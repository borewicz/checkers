#include "boardwindow.h"
#include "ui_boardwindow.h"

BoardWindow::BoardWindow(QWidget *parent) : QWidget(parent), ui(new Ui::BoardWindow)
{
	ui->setupUi(this);
    connect(ui->messegeLineEdit, &QLineEdit::returnPressed, this, &BoardWindow::sendMessage);
    connect(ui->acceptButton, &QPushButton::clicked, this, &BoardWindow::sendMove);
    connect(Socket::getInstance(), &QTcpSocket::readyRead, this, &BoardWindow::parseResponse);
    connect(ui->revokeButton, &QPushButton::clicked, this, &BoardWindow::revokeMoves);
	drawFields();
}

BoardWindow::~BoardWindow()
{
	delete ui;
}

void BoardWindow::drawFields()
{
//    while ( QWidget* w = ui->fieldsGridLayout->findChild<QWidget*>() )
//        delete w;
//    this->setWindowTitle("You are " + QString(isBlack ? "black" : "white"));
    bool isUsed = true;
    for (int i = 0; i < 8; i++)
	{
        isUsed = !isUsed;
        for (int j = 0; j < 8; j++)
		{
            CheckersField *field = new CheckersField(isUsed);
            // pewnie da się ładniej, ale nie mam już do tego gówna cierpliwości
            connect(field, &CheckersField::clicked, field, [=]{ fieldClick(field); });
            ui->fieldsGridLayout->addWidget(field, i, j);
            isUsed = !isUsed;
		}
	}
}

void BoardWindow::fieldClick(CheckersField *field)
{
    if ((!yourTurn) || (ui->fieldsGridLayout->indexOf(field) == -1)) {
        qDebug() << "siki";
        return;
    }

    if (!selectedPawn)
        selectedPawn = field;

    if (currentField) {
        if ((field == currentField) || (field->state() != FieldState::Free))
            return;

        QApplication::restoreOverrideCursor();
        field->setState(color == "black" ? FieldState::Black : FieldState::White);
        currentField = NULL;
        selectedPawn = field;
    }
    else {
        if ((field->state() == FieldState::Free) ||
                (field->state() == (color != "black" ? FieldState::Black : FieldState::White)) ||
                selectedPawn != field)
            return;

        QApplication::setOverrideCursor(Qt::WaitCursor);
        field->setState(FieldState::Free);
        currentField = field;
    }
    int row, col, row_span, col_span;
    ui->fieldsGridLayout->getItemPosition(ui->fieldsGridLayout->indexOf(field), &row, &col, &row_span, &col_span);
    moves.append(color == "black" ? 7 - col : col);
    moves.append(color == "black" ? row : 7 - row);
    updateLabel();
    QApplication::processEvents();
}

void BoardWindow::updateLabel()
{
    if (moves.count() == 0) {
        ui->revokeButton->setEnabled(false);
        ui->acceptButton->setEnabled(false);
    }
    else if (moves.count() % 4 == 0) {
        ui->revokeButton->setEnabled(true);
        ui->acceptButton->setEnabled(true);
    }
}

void BoardWindow::revokeMoves()
{
    while (!moves.empty())
        moves.removeLast();
    updateLabel();
    resetBoard();
    loadBoard();
}

void BoardWindow::resetBoard()
{
    selectedPawn = NULL;
    currentField = NULL;
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        isBlack = !isBlack;
        for (int j = 0; j < 8; j++) {
            int pos = 8*i + j;
            CheckersField *field = (CheckersField *)ui->fieldsGridLayout->itemAt(pos)->widget();
            field->setState((isBlack ? FieldState::Free : FieldState::Null));
            isBlack = !isBlack;
        }
    }
}

void BoardWindow::loadBoard()
{
    int pos = 0;
    for (int i = 0; i < ui->fieldsGridLayout->count(); i++) {
        pos = color == "black" ? (ui->fieldsGridLayout->count()-1)-i : i;
        CheckersField *field = (CheckersField *)ui->fieldsGridLayout->itemAt(pos)->widget();
        switch (board[i/8][i%8])
        {
            case 'w' :
                field->setState(FieldState::White);
                break;
            case 'b' :
                field->setState(FieldState::Black);
                break;
            default:
                break;
        }
    }
}

void BoardWindow::parseResponse()
{
    QString data = QString::fromUtf8(Socket::getInstance()->readAll());
    qDebug() << data;
    QJsonDocument d = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject json = d.object();
    if (json.contains("request"))
    {
        std::string request_type = json["request"].toString().toStdString();
        if (request_type == "message") {
            QDateTime timestamp;
            timestamp.setTime_t(json["timestamp"].toString().toInt());
            ui->chatTextEdit->append("[" + timestamp.toString("hh:mm") + "] " +
                    json["nick"].toString() + ": " + json["message"].toString());
        }
        else if (request_type == "board")
        {
            resetBoard();
            time = json["time"].toString();
            ui->turnsLabel->setText("Turn: " + json["current color"].toString());
            yourTurn = json["current color"].toString() == color ? true : false;

//            ui->chatTextEdit->append("Loading board");
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    board[i][j] = json["board"].toArray()[i].toArray()[j].toString()[0].toLatin1();
            loadBoard();
        }
    }
    else if (json.contains("status"))
    {
        auto status = json["status"].toString();
        if (status != "ok")
        {
            if (status == "wrong move") {
                revokeMoves();
            }
            ui->chatTextEdit->append("Error: " + status);
        }
    }
}

void BoardWindow::sendMessage()
{
    Socket::sendJSON(QJsonObject {
                 { "request", "message" },
                 { "message", ui->messegeLineEdit->text() }
             });
//    ui->chatTextEdit->append(ui->nickLineEdit->text() + ": " + ui->messegeLineEdit->text());
    ui->messegeLineEdit->clear();
}

void BoardWindow::sendMove()
{
    for (int i = moves.size(); i < 20; i++)
    {
        moves.append(-1);
    }
    Socket::sendJSON(QJsonObject {
                 { "request", "movement" },
//                 { "time", (int)QDateTime::currentDateTime().toUTC().toTime_t() },
                 { "time", time },
                 { "movement", moves }
             });
    while (!moves.empty())
        moves.removeLast();
    updateLabel();
}

void BoardWindow::setColor(QString color) {
    this->color = color;
}
