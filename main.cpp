#include "qtodo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qtodo w;
    w.show();
    return a.exec();
}
