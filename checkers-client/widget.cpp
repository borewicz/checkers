#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	connect(ui->connectButton, &QPushButton::clicked, this, &Widget::connectToServer);
    connect(ui->messegeLineEdit, &QLineEdit::returnPressed, this, &Widget::sendMessage);
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
            button->setEnabled(true);
            if (isBlack) button->setStyleSheet("background-color: black; border: none;");
            else button->setStyleSheet("background-color: white; border: none;");
            connect(button, &QPushButton::clicked, [=]{
                int index = ui->fieldsGridLayout->indexOf(button);

                if(index != -1)
                {
                    int row, col, col_span, row_span;
                    ui->fieldsGridLayout->getItemPosition(index, &row, &col, &col_span, &row_span);
                    qDebug() << "Clicked Item is at:" << row << col
                             << "spanning" << row_span << col_span;
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
    try
    {
        QString data = QString::fromUtf8(sock->readAll());
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
    }
    catch (int e)
    {
        ui->chatTextEdit->append("Error occured.");
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

void Widget::sendJSON(QJsonObject json)
{
    if (sock) {
        QJsonDocument doc(json);
        sock->write(QString(doc.toJson(QJsonDocument::Compact)).toUtf8());
    }
}
