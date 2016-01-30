#include "connectwindow.h"
#include "boardwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();
    ConnectWindow window;
    window.show();

    return a.exec();
}
