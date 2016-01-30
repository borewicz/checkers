#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QDialog>
#include <cstdlib>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

#include "sock.h"
#include "boardwindow.h"

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = 0);
    ~ConnectWindow();
    BoardWindow *boardWindow;

private:
    Ui::ConnectWindow *ui;
    void connectToServer();
    void checkConnection();
    void showSocketError();
};

#endif // CONNECTWINDOW_H
