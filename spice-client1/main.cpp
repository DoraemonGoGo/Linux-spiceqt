#include "widget.h"
#include <QApplication>
#include <spicemainwindow.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
//    SpiceMainWindow s;
//    s.show();
    w.show();
    return a.exec();
}
