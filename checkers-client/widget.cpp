#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	connect(ui->connectButton, &QPushButton::clicked, this, &Widget::connectToServer);
    connect(ui->messegeLineEdit, &QLineEdit::returnPressed, this, &Widget::sendMessage);
    connect(ui->sendMoveButton, &QPushButton::clicked, this, &Widget::sendMove);
	drawFields();
}

Widget::~Widget()
{
	delete ui;
}

void Widget::drawFields()
{
    while ( QWidget* w = ui->fieldsGridLayout->findChild<QWidget*>() )
        delete w;
	bool isBlack = true;
    for (int i = 0; i < 8; i++)
	{
		isBlack = !isBlack;
        for (int j = 0; j < 8; j++)
		{
            QPushButton *button = new QPushButton();
			button->setMinimumSize(46, 46);
			button->setMaximumSize(46, 46);
			button->setFlat(true);
            if (!isBlack)
                button->setEnabled(false);
            if (isBlack) button->setStyleSheet("background-color: black; border: none;");
            else button->setStyleSheet("background-color: white; border: none;");
            connect(button, &QPushButton::clicked, [=]{
                int index = ui->fieldsGridLayout->indexOf(button);

                if(index != -1)
                {
                    if (moves.size() % 4 == 2)
                        button->setIcon(QIcon(":/black.png"));
                    else
                        button->setIcon(QIcon());
                    int row, col, col_span, row_span;
                    ui->fieldsGridLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
                    moves.append(col);
                    moves.append(abs(row - 7));
                    qDebug() << col << " " << abs(row - 7);
                }
            });
			button->setAutoFillBackground(true);
            ui->fieldsGridLayout->addWidget(button, i, j);
			isBlack = !isBlack;
		}
	}
}

void Widget::connectToServer()
{
	sock = new QTcpSocket(this);
	connect(sock, &QTcpSocket::readyRead, this, &Widget::parseResponse);
	connect(sock, &QTcpSocket::connected, [&] {
		ui->chatTextEdit->append("Connected to 127.0.0.1");
		ui->messegeLineEdit->setEnabled(true);
	});
	connect(sock, static_cast<void (QTcpSocket::*) (QAbstractSocket::SocketError)>(&QAbstractSocket::error), [&] {
		ui->chatTextEdit->append("Error: " + sock->errorString());
	});
	sock->connectToHost("127.0.0.1", 2137);
    sendJSON(QJsonObject {
                 { "request", "connect" },
                 { "nick", ui->nickLineEdit->text() }
             });
	ui->chatTextEdit->append("Connecting...");
}

void Widget::parseResponse()
{
    QString data = QString::fromUtf8(sock->readAll());
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
            time = json["time"].toString();
//            qDebug() << json["time"];
            ui->chatTextEdit->append("board_id: " + time);
            ui->chatTextEdit->append("Turn: " + json["current color"].toString());
            ui->chatTextEdit->append("Loading board...");
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    board[i][j] = json["board"].toArray()[i].toArray()[j].toString()[0].toLatin1();
//                        drawFields();
                    QPushButton *button = (QPushButton *)ui->fieldsGridLayout->itemAt(8*i+j)->widget();
                    switch (board[i][j])
                    {
                        case 'w' : button->setIcon(QIcon(":/white.png")); // tymczasowe
                            break;
                        case 'b' : button->setIcon(QIcon(":/black.png"));
                               break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    else if (json.contains("color"))
    {
        auto color = json["color"].toString();
        isBlack = (color == "white") ? false : true;
        ui->chatTextEdit->append("You are " + color);
//            isBlack = json["colo"]
    }
    else if (json.contains("status"))
    {
        auto status = json["status"].toString();
        if (status != "ok")
        {
            ui->chatTextEdit->append("Error: " + status);
        }
    }
}

void Widget::sendMessage()
{
    sendJSON(QJsonObject {
                 { "request", "message" },
                 { "message", ui->messegeLineEdit->text() }
             });
    ui->chatTextEdit->append(ui->nickLineEdit->text() + ": " + ui->messegeLineEdit->text());
    ui->messegeLineEdit->clear();
}

void Widget::sendMove()
{
    for (int i = moves.size(); i < 20; i++)
    {
        moves.append(-1);
    }
    sendJSON(QJsonObject {
                 { "request", "movement" },
//                 { "time", (int)QDateTime::currentDateTime().toUTC().toTime_t() },
                 { "time", time },
                 { "movement", moves }
             });
    for (int i = moves.size(); i > 0; i--)
        moves.removeLast();
}

void Widget::sendJSON(QJsonObject json)
{
    if (sock) {
        QJsonDocument doc(json);
        qDebug() << QString(doc.toJson(QJsonDocument::Compact)).toUtf8();
        sock->write(QString(doc.toJson(QJsonDocument::Compact)).toUtf8());
    }
}
