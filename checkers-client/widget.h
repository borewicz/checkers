#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *sock;
    QString time = "0";
    bool isBlack = false;
    void connectToServer();
    void sendMessage();
    void drawFields();
    void parseResponse();
    char board[8][8] = { { '_' } };
    void sendJSON(QJsonObject);
    void fieldClick();
    void sendMove();
//    QList<QPair<int, int>> moves;
    QJsonArray moves;
};

#endif // WIDGET_H
