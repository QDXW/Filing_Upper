#include "mainwindow.h"
#include <Log/Log.h>
#include <QApplication>
#include <QTranslator>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInit();
    MainWindow w;
    w.resize(300,250);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(w.sizePolicy().hasHeightForWidth());
    w.setSizePolicy(sizePolicy);
    w.setWindowOpacity(1);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setMinimumSize(QSize(1920, 1200));
    w.setMaximumSize(QSize(1920, 1200));
    w.setWindowState(false);
    w.setWindowTitle("RL-L100");
    w.show();

    return a.exec();
}
