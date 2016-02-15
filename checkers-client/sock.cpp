#include "sock.h"

bool Socket::instanceFlag = false;
QTcpSocket *Socket::socket = NULL;

QTcpSocket* Socket::getInstance()
{
    if (!instanceFlag) {
        socket = new QTcpSocket();
        instanceFlag = true;
    }
    return socket;
}

QString Socket::readData()
{
    QByteArray dataLength = getInstance()->read(4);
    int length = QString(dataLength).toInt();
    QByteArray data;
    data.append(getInstance()->read(length));
    while (data.length() != length) {
        data.append(getInstance()->read(length - data.length()));
    }
    qDebug() << QString(data);
    return QString(data);
}

void Socket::sendJSON(QJsonObject json)
{
    if (Socket::getInstance()) {
        QJsonDocument doc(json);
        QString body = doc.toJson(QJsonDocument::Compact);
        QString size = QString::number(body.toStdString().size()).rightJustified(4, '0');
        qDebug() << size + body;
        Socket::getInstance()->write((size + body).toUtf8());
    }
}
