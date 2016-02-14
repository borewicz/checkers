#include "connectwindow.h"
#include "ui_connectwindow.h"

ConnectWindow::ConnectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    qsrand(time(NULL));
    ui->nickEdit->setText("Anon" + QString::number(qrand() % 9999));
    ui->nickEdit->setFocus(Qt::OtherFocusReason);
    connect(ui->connectButton, &QPushButton::clicked, this, &ConnectWindow::connectToServer);

    connect(Socket::getInstance(), &QTcpSocket::readyRead, this, &ConnectWindow::checkConnection);
    connect(Socket::getInstance(),
            static_cast<void (QTcpSocket::*) (QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, &ConnectWindow::showSocketError);
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::connectToServer()
{
    Socket::getInstance()->connectToHost(ui->serverEdit->text(), ui->portEdit->text().toInt());
    QJsonObject requestJson;
    requestJson["request"] = "connect";
    requestJson["nick"] = ui->nickEdit->text();
    Socket::sendJSON(requestJson);
}

void ConnectWindow::checkConnection()
{
    QString data = Socket::readData();
//    QString data = QString::fromUtf8(Socket::getInstance()->readAll());
    QJsonDocument d = QJsonDocument::fromJson(data.toUtf8());

    if (d.object().contains("color")) {
        disconnect(Socket::getInstance(), &QTcpSocket::readyRead, this, &ConnectWindow::checkConnection);
        boardWindow = new BoardWindow();
        boardWindow->setColor(d.object()["color"].toString());
        boardWindow->setWindowTitle("Hi, " + ui->nickEdit->text());
        boardWindow->show();
        this->hide();
    }
    else {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Error: " + d.object()["status"].toString() + ".");
        msgBox.exec();
    }
}

void ConnectWindow::showSocketError()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Error occurred: " + Socket::getInstance()->errorString());
    msgBox.exec();
}
