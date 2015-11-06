#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->connectButton, &QPushButton::clicked, this, &Widget::connectToServer);
    connect(ui->messegeLineEdit, &QLineEdit::returnPressed, this, &Widget::sendStatus);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connectToServer()
{
    sock = new QTcpSocket(this);
    connect(sock, &QTcpSocket::readyRead, [&] {
        ui->chatTextEdit->append(QString::fromUtf8(sock->readAll()));
    });
    connect(sock, &QTcpSocket::connected, [&] {
        ui->chatTextEdit->append("Connected to [address]");
        sock->write(QString("guwno").toUtf8());
    });
    connect(sock, static_cast<void (QTcpSocket::*) (QAbstractSocket::SocketError)>(&QAbstractSocket::error), [&] {
        ui->chatTextEdit->append("Error: " + sock->errorString());
    });
    sock->connectToHost("127.0.0.1", 9000);
}

void Widget::sendStatus()
{
    QJsonObject json {
        { "nick", "guwno" },
        { "status", "MESSAGE" },
        { "message", ui->messegeLineEdit->text() }
    };
    QJsonDocument doc(json);
    sock->write(QString(doc.toJson(QJsonDocument::Compact)).toUtf8());
    ui->messegeLineEdit->clear();
}
