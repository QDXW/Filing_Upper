#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QStandardItem>
#include <QDateTime>
#include <QDir>
#include <QTextStream>
#include <QVector>
#include <QPen>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include <command.h>
#include "common/CRC16.h"
#include "Signalprocess/qrcode.h"
#include "editsize.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  
    int CommandSend(int cmdDataNum, quint8 cmdType, quint8 cmdCode, quint8* bypass);


private slots:
    void on_Connect_Btn_clicked();
    void ReadData();
    void SearchPort();
    void Rrrorhandle(QSerialPort::SerialPortError a);

    void on_PUMP_WASH_clicked();

    void on_Quit_clicked();

    void on_Set_Injuct_R1_clicked();

    void on_Set_Injuct_R2_clicked();

    void on_Set_Injuct_M_clicked();

    void on_Set_Injuct_W_clicked();

//    void on_Set_Injuct_Base_clicked();

    void on_L100_Filling_clicked();


    void on_Padding_clicked();

    void on_PUMP_WASH_All_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel* dataModel;          //绑定表格Tableview

    QList<float> Showdata;                  //原始表格数据临时存储
    QList<float> SaveShowdata[300];              //保存表格数据
    int SaveShowdataIndex = 0;

    EditSize *Edit_Vol;
    int index=0;

    QTimer *SearchPortT;                    //刷新端口定时器

    QSerialPort *SerialPort;                //传输绑定的端口
    QSerialPort *SerialPort2;               //刷新端口绑定的端口

    quint8 cmdBuffer[200];

    int contReceive = 0;
    int respLength = 0;
    int bytesReceived = 0;
    int getResponse = 0;

    int OFFSET_HEADER = 0;
    int OFFSET_LEN_LO = 1;
    int OFFSET_LEN_HI = 2;
    int OFFSET_CMD_TYPE = 3;
    int OFFSET_CMD_CODE = 4;
    int OFFSET_CMD_DATA = 5;

    int LEN_HEAD_LENGTH = 3;
    int LEN_HEAD_TAIL = 2;
    quint8 start = 1;

};

#endif // MAINWINDOW_H
