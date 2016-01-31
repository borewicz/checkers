#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>

#include "sock.h"

namespace Ui {
class BoardWindow;
}

class BoardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = 0);
    ~BoardWindow();
    void setColor(QString color) {
        colorId = (color == "black") ? true : false;
    }

private:
    // const
    const QString BLACK_IMG = ":/black.png";
    const QString WHITE_IMG = ":/white.png";
    const QString NULL_IMG = ":/null_white.png";
    const QString BLANK_IMG = ":/null_black.png";

    // variables
    Ui::BoardWindow *ui;
    QString time = "0"; // act as board id
    int colorId = 0; // 0 - white, 1 - black
    char board[8][8] = { { '_' } };
    QJsonArray moves; // it's ugly, but it works xD

    // methods
    void connectToServer();
    void sendMessage();
    void drawFields();
    void parseResponse();
    void resetBoard();
    void loadBoard();
    void revokeMoves();
    void fieldClick();
    void sendMove();
    void updateLabel();
    void lockFields();
};

#endif // WIDGET_H
