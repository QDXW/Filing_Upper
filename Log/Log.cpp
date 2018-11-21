#include "Log.h"

QMutex mutex;//日志代码互斥锁
QString timePoint;

void LogMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
     mutex.lock();
     cout << msg.toStdString() << endl;
     //Critical Resource of Code
     QByteArray localMsg = msg.toLocal8Bit();
     QString log;

     switch (type) 
     {
         case QtDebugMsg:
             log.append(QString("%1 %2").arg(msg).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")));
             break;
         case QtInfoMsg:
             log.append(QString("Info: %1  %2  %3  %4  %5").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")));
             break;
         case QtWarningMsg:
             log.append(QString("Warning: %1  %2  %3  %4  %5").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")));
             break;
         case QtCriticalMsg:
             log.append(QString("Critical: %1  %2  %3  %4  %5").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")));
             break;
         case QtFatalMsg:
             log.append(QString("Fatal: %1  %2  %3  %4  %5").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")));
             abort();
     }

     QFile file;
     QDir dir;
     dir.cd(QDir::currentPath());
     if(!dir.exists("Log"))
     {
         dir.mkdir("Log");
     }

     QString path = QString("Log/Log%1.log").arg(timePoint);

     file.setFileName(path);
     if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
     {
         QString erinfo = file.errorString();
         cout << erinfo.toStdString() << endl;
         mutex.unlock();
         return;
     }

     QTextStream out(&file);
     out << "\n\r" << log;
     file.close();

     mutex.unlock();
}

void LogInit(void)
{
    //release模式下，调试信息输出至日志文件
#ifndef _DEBUG
    timePoint = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    qInstallMessageHandler(LogMsgOutput);
#endif
}
