#ifndef LOG_H
#define LOG_H

#include <QApplication>
#include <QObject>
#include <iostream>
#include <cstdlib>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QDir>
using namespace std;

extern void LogInit(void);

#endif // LOG_H
