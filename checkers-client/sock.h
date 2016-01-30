#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Socket:public QTcpSocket {

private:
    static bool instanceFlag;
    static QTcpSocket *socket;
    Socket();
public:    
    static QTcpSocket* getInstance();
    static void sendJSON(QJsonObject json);
};

#endif // CONNECTION_H
