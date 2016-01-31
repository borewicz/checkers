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
    while ( QWidget* w = ui->fieldsGridLayout->findChild<QWidget*>() )
        delete w;
//    this->setWindowTitle("You are " + QString(isBlack ? "black" : "white"));
    bool isBlack = true;
    for (int i = 0; i < 8; i++)
	{
        isBlack = !isBlack;
        for (int j = 0; j < 8; j++)
		{
            QPushButton *button = new QPushButton();
            button->setMinimumSize(60, 60);
            button->setMaximumSize(60, 60);
			button->setFlat(true);
            button->setAutoFillBackground(true);
            button->setIconSize(QSize(60,60));
            button->setStyleSheet("border: none;");
            if (isBlack) {
                button->setIcon(QIcon(BLANK_IMG));
            }
            else {
                button->setEnabled(false);
                button->setIcon(QIcon(NULL_IMG));
            }
            connect(button, &QPushButton::clicked, [=]{
                int index = ui->fieldsGridLayout->indexOf(button);

                if (index != -1)
                {
                    if (moves.size() % 4 == 2) {
                        QApplication::restoreOverrideCursor();
                        button->setIcon(QIcon((this->colorId ? BLACK_IMG : WHITE_IMG)));
                        /* TODO
                         * - własna funkcja (obudowa na setIcon)
                         * - kopia boardu i na niej operowanie
                         */
                        //setFieldStatus(&button, (this->colorId ? BLACK_IMG : WHITE_IMG));
                    }
                    else {
                        QApplication::setOverrideCursor(Qt::WaitCursor);
                        button->setIcon(QIcon(BLANK_IMG));
                    }
                    QApplication::processEvents();

                    int row, col, col_span, row_span;
                    ui->fieldsGridLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
                    moves.append(this->colorId ? 7 - col : col);
                    moves.append(this->colorId ? row : 7 - row);
                    updateLabel();
                }
            });
            ui->fieldsGridLayout->addWidget(button, i, j);
            isBlack = !isBlack;
		}
	}
}

void BoardWindow::updateLabel()
{
    qDebug() << moves.count();
    if (moves.count() == 0) {
        ui->turnsLabel->setText("No moves.");
        ui->revokeButton->setEnabled(false);
        ui->acceptButton->setEnabled(false);
    }
    else if (moves.count() % 4 == 0) {
        ui->turnsLabel->setText("Moves done: " + QString::number(moves.count()/4));
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
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        isBlack = !isBlack;
        for (int j = 0; j < 8; j++) {
            int pos = 8*i + j;
            QPushButton *button = (QPushButton *)ui->fieldsGridLayout->itemAt(pos)->widget();
            button->setIcon(QIcon(isBlack ? BLANK_IMG : NULL_IMG));
            isBlack = !isBlack;
        }
    }
}

void BoardWindow::loadBoard()
{
    int pos = 0;
    for (int i = 0; i < ui->fieldsGridLayout->count(); i++) {
        pos = colorId ? (ui->fieldsGridLayout->count()-1)-i : i;
        QPushButton *button = (QPushButton *)ui->fieldsGridLayout->itemAt(pos)->widget();
        switch (board[i/8][i%8])
        {
            case 'w' : button->setIcon(QIcon(WHITE_IMG));
//                (colorId) ? button->setEnabled(false) : button->setEnabled(true);
                break;
            case 'b' : button->setIcon(QIcon(BLACK_IMG));
//                (!colorId) ? button->setEnabled(false) : button->setEnabled(true);
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
        if (request_type == "message")
            ui->chatTextEdit->append("[" + json["timestamp"].toString() + "] " +
                    json["nick"].toString() + ": " + json["message"].toString());
        else if (request_type == "board")
        {
            resetBoard();
            time = json["time"].toString();
            ui->chatTextEdit->append("Loading board, turn: " + json["current color"].toString());
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    board[i][j] = json["board"].toArray()[i].toArray()[j].toString()[0].toLatin1();
            loadBoard();
            qDebug() << ui->fieldsGridLayout->count();
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
