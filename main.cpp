#include "mainwindow.h"
#include <Log/Log.h>
#include <QApplication>
#include <QTranslator>
#include <QLabel>
#include <QMovie>

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
    w.setMinimumSize(QSize(1280, 800));
    w.setMaximumSize(QSize(1280, 800));
    w.setWindowState(false);

    w.show();
    return a.exec();
}
