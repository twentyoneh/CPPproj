#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/Utils/memoryAnalizer1.png"));
    MainWindow w;
    w.setWindowTitle("Memory Analizer");
    w.show();
    return a.exec();
}
