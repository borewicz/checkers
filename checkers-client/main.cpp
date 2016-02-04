#include "connectwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectWindow window;
    window.show();

    return a.exec();
}
