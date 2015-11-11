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
			button->setEnabled(false);
            if (isBlack) button->setStyleSheet("background-color: black; border: none;");
			else button->setStyleSheet("background-color: white; border: none;");
			button->setAutoFillBackground(true);
			//            button->setIcon(QIcon(":/null.png"));
			//            button->setIconSize(QSize(46, 46));
			//            button->setStyleSheet(""
			//                     "background-repeat: no-repeat;"
			//                     "background-position: center center");
			//            connect(button, QtCore.SIGNAL("clicked()"),
			//                lambda i=i, j=j: self.sendMove(i, j))
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
                        QPushButton *button = ui->fieldsGridLayout->findChild<QPushButton*>(ui->fieldsGridLayout->itemAtPosition(i,j)->widget()->objectName());
                        ui->chatTextEdit->append(QString::number(ui->fieldsGridLayout->count()));
                        if (button)
                            button->setText(json["board"].toArray()[i].toArray()[j].toString());
//                        switch (json["board"].toArray()[i].toArray()[j].toString().toStdString()[0])
//                        {
//                            case 'w' : button->setIcon(QIcon(":/white.png"));
//                                break;
//                            case 'b' : button->setIcon(QIcon(":/black.png"));
//                                break;
//                        }
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
    if (sock) {
		QJsonObject json {
            { "request", "message" },
//			{ "nick", ui->nickLineEdit->text() },
            { "message", ui->messegeLineEdit->text() }
		};
		QJsonDocument doc(json);
		sock->write(QString(doc.toJson(QJsonDocument::Compact)).toUtf8());
		ui->chatTextEdit->append(ui->nickLineEdit->text() + ": " + ui->messegeLineEdit->text());
		ui->messegeLineEdit->clear();
	}
}
