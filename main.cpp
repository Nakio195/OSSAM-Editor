#include "MainWindow.h"
#include <QApplication>

#include "widgets/OSSAM_World.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
