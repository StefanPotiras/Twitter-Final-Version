#include "Twitter.h"
#include <QtWidgets/QApplication>
#include <sqlite3.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Twitter w;
    w.show();

    return a.exec();
}