#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <QMessageBox>

#include "sock.h"
#include "checkersfield.h"

namespace Ui {
class BoardWindow;
}

class BoardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = 0);
    ~BoardWindow();
    void setColor(QString color);

private:
    // variables
    Ui::BoardWindow *ui;
    QString time = "0"; // act as board id
    QString color; // 0 - white, 1 - black
    char board[8][8] = { { '_' } };
    CheckersField *currentField = NULL, *selectedPawn = NULL;
    QJsonArray moves; // it's ugly, but it works xD
    bool yourTurn, waiting = false;

    // methods
    void connectToServer();
    void sendMessage();
    void drawFields();
    void getReady();
    void parseResponse();
    void resetBoard();
    void loadBoard();
    void revokeMoves();
    void sendMove();
    void updateLabel();
    void lockFields();
    void fieldClick(CheckersField*);
};

#endif // WIDGET_H
