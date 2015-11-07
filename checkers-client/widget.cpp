#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, &QPushButton::clicked, this, &Widget::connectToServer);
    connect(ui->messegeLineEdit, &QLineEdit::returnPressed, this, &Widget::sendStatus);
    drawFields();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawFields()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            QPushButton *button = new QPushButton();
            button->setMinimumSize(46, 46);
            button->setMaximumSize(46, 46);
            button->setFlat(true);
            button->setEnabled(false);
            button->setAutoFillBackground(true);
            button->setIcon(QIcon(":/null.png"));
            button->setIconSize(QSize(46, 46));
            button->setStyleSheet(""
                     "background-repeat: no-repeat;"
                     "background-position: center center");
//            connect(button, QtCore.SIGNAL("clicked()"),
//                lambda i=i, j=j: self.sendMove(i, j))
            ui->fieldsGridLayout->addWidget(button, i, j);
        }
    }
}

void Widget::connectToServer()
{
    sock = new QTcpSocket(this);
    connect(sock, &QTcpSocket::readyRead, [&] {
        ui->chatTextEdit->append(QString::fromUtf8(sock->readAll()));
    });
    connect(sock, &QTcpSocket::connected, [&] {
        ui->chatTextEdit->append("Connected to 127.0.0.1");
        sock->write(QString("guwno").toUtf8());
    });
    connect(sock, static_cast<void (QTcpSocket::*) (QAbstractSocket::SocketError)>(&QAbstractSocket::error), [&] {
        ui->chatTextEdit->append("Error: " + sock->errorString());
    });
    sock->connectToHost("127.0.0.1", 2137);
    ui->chatTextEdit->append("Connecting...");
}

void Widget::sendStatus()
{
    QJsonObject json {
        { "nick", "guwno" },
        { "message", ui->messegeLineEdit->text() }
    };
    QJsonDocument doc(json);
    sock->write(QString(doc.toJson(QJsonDocument::Compact)).toUtf8());
    ui->messegeLineEdit->clear();
}
