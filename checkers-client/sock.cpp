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
void Socket::sendJSON(QJsonObject json)
{
    if (Socket::getInstance()) {
        QJsonDocument doc(json);
        QString body = doc.toJson(QJsonDocument::Compact);
        QString size = QString::number(body.size()).rightJustified(4, '0');
        qDebug() << size + body;
        Socket::getInstance()->write((size + body).toUtf8());
    }
}
