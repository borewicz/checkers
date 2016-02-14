#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>

class Socket:public QTcpSocket {

private:
    static bool instanceFlag;
    static QTcpSocket *socket;
    Socket();
public:    
    static QTcpSocket* getInstance();
    static QString readData();
    static void sendJSON(QJsonObject json);
};

#endif // CONNECTION_H
