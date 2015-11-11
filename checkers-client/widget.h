#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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
    void connectToServer();
    void sendMessage();
    void drawFields();
    void parseResponse();
    char board[8][8] = { { '_' } };
};

#endif // WIDGET_H
