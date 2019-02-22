#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QMovie"

//extern "C" void test();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialPort = new QSerialPort(this);
    SerialPort2 = new QSerialPort(this);

    dataModel = new QStandardItemModel();

    SerialPort->setDataBits(QSerialPort::Data8);
    SerialPort->setParity(QSerialPort::NoParity);
    SerialPort->setStopBits(QSerialPort::OneStop);
    SerialPort->setBaudRate(115200);
    connect(SerialPort,SIGNAL(readyRead()),this,SLOT(ReadData()));

    SearchPortT = new QTimer;
    SearchPortT->setInterval(200);
    connect(SearchPortT, SIGNAL(timeout()), this, SLOT(SearchPort()));
    SearchPortT->start(100);

    connect(SerialPort,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(Rrrorhandle(QSerialPort::SerialPortError)));

    ui->Injuct_Count_R1->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_R2->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_M->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_W1->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_W2->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_W3->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_W4->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_W5->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_W6->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_Base->setValidator(new QIntValidator(1, 100, this));

    ui->groupBox->setEnabled(false);
}

void MainWindow::Rrrorhandle(QSerialPort::SerialPortError ror)
{
    qDebug()<<ror;
}
MainWindow::~MainWindow()
{
    delete ui;
}

/*连接*/
void MainWindow::on_Connect_Btn_clicked()
{
    if(ui->Connect_Btn->text()==tr("连接"))
    { 
        if(ui->Connect_Btn->text()==tr("连接"))
        {
            SerialPort->setPortName(ui->COMSelectcomboBox->currentText());
            SerialPort->setFlowControl(QSerialPort::NoFlowControl);
            if(SerialPort->open(QIODevice::ReadWrite))
            {
                ui->Connect_Btn->setText("断开");
                ui->COMSelectcomboBox->setEnabled(false);
                SearchPortT->stop();
//                ui->groupBox->setEnabled(true);
            }
            else
            {
                QMessageBox::warning(this,tr("警告"),tr("打开串口失败\r\n该串口被占用或者未选择正确的串口"));
            }
        }

        quint8 DATA = 1;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_CONNECT,&DATA);
    }
    else
    {
        ui->Connect_Btn->setText("连接");
        ui->COMSelectcomboBox->setEnabled(true);
        SerialPort->clear();
        SerialPort->close();
        SearchPortT->start();
    }
}

/*串口插入添加，拔出清除*/
void MainWindow::SearchPort()
{
    QStringList ComList;
    QList<int> Index;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        SerialPort2->setPort(info);
        SerialPort2->open(QIODevice::ReadWrite);
        ComList += SerialPort2->portName();
        SerialPort2->clear();
        SerialPort2->close();
    }
    for(int i=0;i< ComList.length();i++)
    {
       for(int j=0;j< ui->COMSelectcomboBox->count();j++)
       {
           if(ComList.at(i) == ui->COMSelectcomboBox->itemText(j))
           {
               Index.append(i);
               break;
           }
           else
           {
           }
        }
    }
    for(int i=0;i< ComList.length();i++)
    {
        if(Index.contains(i))
        {
        }
        else
        {
          ui->COMSelectcomboBox->addItem(ComList.at(i));
         qDebug("add");
        }
    }

    //拔出清除
    for(int i=0;i<ui->COMSelectcomboBox->count();i++)
    {
        if(ComList.contains(ui->COMSelectcomboBox->itemText(i)))
        {

        }
        else
        {
            ui->COMSelectcomboBox->removeItem(i);
            qDebug("rm ");
        }
    }
}

/***********************************************************************************************
*函数名: CommandSend
*函数功能描述:串口发送函数
*函数参数:无
*函数返回值: 无
***********************************************************************************************/
int MainWindow::CommandSend(int cmdDataNum, quint8 cmdType, quint8 cmdCode, quint8* bypass)
{
    start = 0;
    int SIZE_LEN_HEAD_CMD_CRC = 6;
    uint16 totalPackageLength = SIZE_LEN_HEAD_CMD_CRC + cmdDataNum + 2;
    uint16 packageLength = SIZE_LEN_HEAD_CMD_CRC + cmdDataNum;
    uint16 crcCal = 0;
    QString str;

    /* Head */
    cmdBuffer[OFFSET_HEADER] = (char)'$';

    /* Package length */
    cmdBuffer[OFFSET_LEN_LO] = (uint8)(packageLength & 0x00FF);
    cmdBuffer[OFFSET_LEN_HI] = (uint8)((packageLength & 0xFF00)>>8);

    /* Command type and code */
    cmdBuffer[OFFSET_CMD_TYPE] = cmdType;
    cmdBuffer[OFFSET_CMD_CODE] = cmdCode;
    memcpy(&cmdBuffer[OFFSET_CMD_DATA],bypass,cmdDataNum);

    /* Calculate CRC, exclude 2-bytes crc value */
    crcCal = CRC16_Calculate(cmdBuffer, (uint32)(packageLength - 2), 0xFFFF, 0);

    /* CRC */
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum] = crcCal& 0x00FF;
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum + 1] = (crcCal & 0xFF00)>>8;

    /* Tail */
    cmdBuffer[OFFSET_CMD_DATA + cmdDataNum + 2] = (char)'#';
    QByteArray data = QByteArray((const char*)cmdBuffer,totalPackageLength);

    QString Str;
    for(int i = 0; i < data.length(); i++)
    {
       Str.append(tr("%1").arg(data[i]&0xFF,2, 16, QLatin1Char('0')).toUpper() + QString(" "));
    }
    qDebug()<<Str;
    Str.clear();

    if(ui->Connect_Btn->text() == tr("断开"))
    {
        if(!SerialPort->write(data))
        {
            qDebug("发送失败！");
        }
    }
    else
    {
        QMessageBox::warning(this,tr("串口问题"),tr("串口未连接，请先连接串口。"));
    }
    start = 1;
    return 0;
}

/***********************************************************************************************
*函数名: ReadData
*函数功能描述:串口接收并处理数据函数
*函数参数:无
*函数返回值: 无
***********************************************************************************************/
void MainWindow::ReadData()
{
    static QByteArray ReadBuff;
    static QByteArray ReadBuff_All;
    quint8  stdid,RecvBuff[4096];
    quint16 Datalength = 0,Total_Length = 0;
    QString Str;
    ReadBuff_All = SerialPort->readAll();

    /* 先拼接数据，得到完整数据，否则就退出舍弃本次数据 */
    if(ReadBuff_All[0] != '$')
    {
        if(ReadBuff[0] != '$')
        {
            ReadBuff.clear();
            ReadBuff_All.clear();
            return;
        }
        else
        {
            ReadBuff.append(ReadBuff_All);
            if(ReadBuff[(ReadBuff.length() - 1)] != '#')
            {
                return;
            }
        }
    }
    else
    {
        if(ReadBuff_All[(ReadBuff_All.length() - 1)] != '#')
        {
            ReadBuff.clear();
            ReadBuff.append(ReadBuff_All);
            return;
        }
        else
        {
            ReadBuff.clear();
            ReadBuff.append(ReadBuff_All);
        }
    }

    /* 对符合要求的数据进行处理 */
    memset(RecvBuff,0,3000);
    memcpy(&RecvBuff[0],ReadBuff,ReadBuff.length());
    Total_Length = ReadBuff.length();
    ReadBuff.clear();

    for(int i = 0; i < Total_Length; i++)
    {
       Str.append(tr("%1").arg(RecvBuff[i]&0xFF,2, 16, QLatin1Char('0')).toUpper() + QString(" "));
    }
    qDebug()<<Str;
    Str.clear();
    memcpy(&Datalength,&RecvBuff[1],2);
    stdid = RecvBuff[4];
    switch(stdid)
    {
    case CMD_CODE_BUMP_FILLING:
        if(RecvBuff[5])
            ui->L100_Filling->setText(tr("正在罐装"));
        else
            ui->L100_Filling->setText(tr("开始罐装"));
        break;

    case CMD_CODE_WASH:
        if(RecvBuff[5])
            ui->PUMP_WASH->setText(tr("正在清洗"));
        else
            ui->PUMP_WASH->setText(tr("开始清洗"));
        break;

    case CMD_CODE_INJUCET_VOLUME_R1:
        QMessageBox::warning(this,tr("温馨提醒"),tr("R1注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_R2:
       QMessageBox::warning(this,tr("温馨提醒"),tr("R2注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_M:
        QMessageBox::warning(this,tr("温馨提醒"),tr("M注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W1:
        QMessageBox::warning(this,tr("温馨提醒"),tr("W1注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W2:
       QMessageBox::warning(this,tr("温馨提醒"),tr("W2注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W3:
        QMessageBox::warning(this,tr("温馨提醒"),tr("W3注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W4:
        QMessageBox::warning(this,tr("温馨提醒"),tr("W4注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W5:
        QMessageBox::warning(this,tr("温馨提醒"),tr("W5注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_W6:
        QMessageBox::warning(this,tr("温馨提醒"),tr("W6注液量设置成功！"));
        break;

    case CMD_CODE_INJUCET_VOLUME_BASE:
        QMessageBox::warning(this,tr("温馨提醒"),tr("底物注液量设置成功！"));
        break;

        default:
        break;
     }
     ReadBuff.clear();
}

void MainWindow::on_PUMP_WASH_clicked()
{
    quint8 DATA = 0;
    if(ui->PUMP_WASH->text()==tr("开始清洗"))
    {
//       DATA = ui->Wash_Time->text().toInt();
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_WASH,&DATA);
    }
    else
    {
       DATA = 0;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_WASH,&DATA);
    }
}

void MainWindow::on_Quit_clicked()
{
     this->close();
}

void MainWindow::on_Set_Injuct_R1_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_R1->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_R1,Buf);
}

void MainWindow::on_Set_Injuct_R2_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_R2->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_R2,Buf);
}

void MainWindow::on_Set_Injuct_M_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_M->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_M,Buf);
}

void MainWindow::on_Set_Injuct_W1_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W1->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W1,Buf);
}

void MainWindow::on_Set_Injuct_W2_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W2->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W2,Buf);
}

void MainWindow::on_Set_Injuct_W3_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W3->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W3,Buf);
}

void MainWindow::on_Set_Injuct_W4_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W4->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W4,Buf);
}

void MainWindow::on_Set_Injuct_W5_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W5->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W5,Buf);
}

void MainWindow::on_Set_Injuct_W6_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_W6->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_W6,Buf);
}

void MainWindow::on_Set_Injuct_Base_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_Base->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME_BASE,Buf);
}

//void MainWindow::on_RETURN_ZERO_clicked()
//{
//    quint8 Buf[2] = {0};
//    CommandSend(2,CMD_TYPE_APP, CMD_CODE_RETURN_ZERO,Buf);
//}

//void MainWindow::on_BUMP_INT_clicked()
//{
//    quint8 DATA = 1;
//    if(ui->BUMP_INT->text()==tr("初始化泵"))
//    {
//       CommandSend(1,CMD_TYPE_APP, CMD_CODE_BUMP_INT,&DATA);
//    }
//    else
//    {
//       DATA = 0;
//       CommandSend(1,CMD_TYPE_APP, CMD_CODE_BUMP_INT,&DATA);
//    }
//}

void MainWindow::on_L100_Filling_clicked()
{
    quint8 DATA = 1;
    if(ui->L100_Filling->text()==tr("开始灌装"))
    {
        ui->L100_Filling->setText(tr("正在罐装"));
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_BUMP_FILLING,&DATA);
    }
    else
    {
       DATA = 0;
       ui->L100_Filling->setText(tr("开始罐装"));
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_BUMP_FILLING,&DATA);
    }
}
