#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

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
    ui->groupBox->setEnabled(false);

    ui->Warm_Temp->setValidator(new QIntValidator(1, 240, this));
    ui->Warm_Time->setValidator(new QIntValidator(1, 20, this));
    ui->Injuct_Count_1->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_2->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_3->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_4->setValidator(new QIntValidator(1, 500, this));
    ui->Injuct_Count_5->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_6->setValidator(new QIntValidator(1, 100, this));
    ui->Injuct_Count_7->setValidator(new QIntValidator(1, 100, this));

    QRegExp Injuct_Time("[1-9][0-9][0]{2}");
    QValidator *Injuct = new QRegExpValidator(Injuct_Time,this);
    ui->Injuct_Time ->setValidator(Injuct);

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
        ui->groupBox->setEnabled(false);
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

void MainWindow::ReadData()
{
    if(start)
    {
        float Temp_HOT1,Temp_HOT2;
        static QByteArray ReadBuff;
        quint8  stdid,RecvBuff[4096];
        quint16 Datalength = 0,Total_Length = 0;
        QString Str;
        ReadBuff.append(SerialPort->readAll());
        memset(RecvBuff,0,3000);
        memcpy(&RecvBuff[0],ReadBuff,ReadBuff.length());
        Total_Length = ReadBuff.length();
        ReadBuff.clear();

        if(ui->Connect_Btn->text()==tr("连接"))
        {
            if((RecvBuff[0] != '$') && (RecvBuff[Datalength+1] != '#'))
            {
                ui->Connect_Btn->setText("连接");
                return;
            }
        }

        for(int i = 0; i < Total_Length; i++)
        {
           Str.append(tr("%1").arg(RecvBuff[i]&0xFF,2, 16, QLatin1Char('0')).toUpper() + QString(" "));
        }
        qDebug()<<Str;
        Str.clear();
        memcpy(&Datalength,&RecvBuff[1],2);
        if(RecvBuff[0] == '$')
        {
            if(RecvBuff[Datalength+1] == '#')
            {
                stdid = RecvBuff[4];
                switch(stdid)
                {
                case CMD_CODE_TEMP:
                    memcpy(&Temp_HOT1,&RecvBuff[5],4);
                    ui->Temp_Display->setText(tr("%1").arg(Temp_HOT1));
                    memcpy(&Temp_HOT2,&RecvBuff[9],4);
                    ui->Temp_Display_2->setText(tr("%1").arg(Temp_HOT2));
                    break;

                case CMD_CODE_SUCCESS:
                    if(RecvBuff[5])
                    {
                        ui->L100_Switch->setText(tr("Open"));
                        ui->groupBox->setEnabled(true);
                    }
                    else
                    {
                        QMessageBox msgBox(QMessageBox::Warning, tr("温度警告"),tr("未达到指定温度"),
                                           0, this);
                        msgBox.addButton(tr("确定"), QMessageBox::AcceptRole);
                        ReadBuff.clear();
                        msgBox.exec();
                    }
                    break;

                case CMD_CODE_APPARATUS_ACHIEVE:
                    if(RecvBuff[5])
                        ui->Start_Appratus->setText(tr("正在覆膜"));
                    else
                        ui->Start_Appratus->setText(tr("开始覆膜"));
                    break;

                case CMD_CODE_INITAILIZE:
                    if(RecvBuff[5])
                    {
                        ui->L100_Switch->setText(tr("Closed"));
                        ui->L100_INJECT->setText(tr("开始灌装"));
                        ui->Start_Appratus->setText(tr("开始覆膜"));
                        ui->Injuct_Count_1->setText(tr("500"));
                        ui->Injuct_Count_2->setText(tr("500"));
                        ui->Injuct_Count_3->setText(tr("500"));
                        ui->Injuct_Count_4->setText(tr("500"));
                        ui->Injuct_Count_5->setText(tr("100"));
                        ui->Injuct_Count_6->setText(tr("100"));
                        ui->Injuct_Count_7->setText(tr("100"));
                        ui->Injuct_Time->setText(tr("900"));
                        ui->Injuct_Bump1->setText(tr("关闭注射泵1"));
                        ui->Injuct_Bump2->setText(tr("关闭注射泵2"));
                        ui->Injuct_Bump3->setText(tr("关闭注射泵3"));
                        ui->Injuct_Bump4->setText(tr("关闭注射泵4"));
                        ui->Injuct_Bump5->setText(tr("关闭注射泵5"));
                        ui->Injuct_Bump6->setText(tr("关闭注射泵6"));
                        ui->Injuct_Bump7->setText(tr("关闭注射泵7"));
                        ui->Press_Plate->setText(tr("压板下降"));
                        ui->groupBox->setEnabled(false);
                    }
                    break;

                case CMD_CODE_INJECT:
                    if(RecvBuff[5])
                        ui->L100_INJECT->setText(tr("正在灌装"));
                    else
                        ui->L100_INJECT->setText(tr("开始灌装"));
                    break;

                case CMD_CODE_EXHAUST_AIR:
                    if(RecvBuff[5])
                        ui->Exhaust_AIR->setText(tr("正在排空"));
                    else
                        ui->Exhaust_AIR->setText(tr("开始排空"));
                    break;

                case CMD_CODE_RECYCLE:
                    if(RecvBuff[5])
                        ui->RECYCLE->setText(tr("正在回收"));
                    else
                        ui->RECYCLE->setText(tr("开始回收"));
                    break;

                case CMD_CODE_WARM_BLOCK1:
                    if(RecvBuff[5])
                        ui->Control_Temp1->setText(tr("关闭加热块1"));
                    else
                        ui->Control_Temp1->setText(tr("打开加热块1"));
                    break;

                case CMD_CODE_WARM_BLOCK2:
                    if(RecvBuff[5])
                        ui->Control_Temp2->setText(tr("关闭加热块2"));
                    else
                        ui->Control_Temp2->setText(tr("打开加热块2"));
                    break;

                case CMD_CODE_CARVE_DIRECTION:
                    if(RecvBuff[5])
                        ui->Open_Carve->setText(tr("反向切割"));
                    else
                        ui->Open_Carve->setText(tr("正向切割"));
                    break;

                case CMD_CODE_WARM_BUMP:
                    if(RecvBuff[5])
                        ui->Bumping_post1->setText(tr("关闭加热挡柱"));
                    else
                        ui->Bumping_post1->setText(tr("打开加热挡柱"));
                    break;

                case CMD_CODE_CARVE_BUMP:
                    if(RecvBuff[5])
                        ui->Bumping_post2->setText(tr("关闭切割挡柱"));
                    else
                        ui->Bumping_post2->setText(tr("打开切割挡柱"));
                    break;

                case CMD_CODE_PRESS_PLATE:
                    if(RecvBuff[5])
                        ui->Press_Plate->setText(tr("压板上升"));
                    else
                        ui->Press_Plate->setText(tr("压板下降"));
                    break;

                case CMD_CODE_INJUCET_BUMP:
                    switch(RecvBuff[6])
                    {
                    case 0:
                        ui->Injuct_Bump1->setText(tr("打开注射泵1"));
                        ui->Injuct_Bump2->setText(tr("打开注射泵2"));
                        ui->Injuct_Bump3->setText(tr("打开注射泵3"));
                        ui->Injuct_Bump4->setText(tr("打开注射泵4"));
                        ui->Injuct_Bump5->setText(tr("打开注射泵5"));
                        ui->Injuct_Bump6->setText(tr("打开注射泵6"));
                        ui->Injuct_Bump7->setText(tr("打开注射泵7"));
                        break;
                    case 1:
                        if(RecvBuff[5])
                            ui->Injuct_Bump1->setText(tr("关闭注射泵1"));
                        else
                            ui->Injuct_Bump1->setText(tr("打开注射泵1"));
                        break;

                    case 2:
                        if(RecvBuff[5])
                            ui->Injuct_Bump2->setText(tr("关闭注射泵2"));
                        else
                            ui->Injuct_Bump2->setText(tr("打开注射泵2"));
                        break;

                    case 3:
                        if(RecvBuff[5])
                            ui->Injuct_Bump3->setText(tr("关闭注射泵3"));
                        else
                            ui->Injuct_Bump3->setText(tr("打开注射泵3"));
                        break;

                    case 4:
                        if(RecvBuff[5])
                            ui->Injuct_Bump4->setText(tr("关闭注射泵4"));
                        else
                            ui->Injuct_Bump4->setText(tr("打开注射泵4"));
                        break;

                    case 5:
                        if(RecvBuff[5])
                            ui->Injuct_Bump5->setText(tr("关闭注射泵5"));
                        else
                            ui->Injuct_Bump5->setText(tr("打开注射泵5"));
                        break;

                    case 6:
                        if(RecvBuff[5])
                            ui->Injuct_Bump6->setText(tr("关闭注射泵6"));
                        else
                            ui->Injuct_Bump6->setText(tr("打开注射泵6"));
                        break;

                    case 7:
                        if(RecvBuff[5])
                            ui->Injuct_Bump7->setText(tr("关闭注射泵7"));
                        else
                            ui->Injuct_Bump7->setText(tr("打开注射泵7"));
                        break;

                    case 8:
                        ui->Injuct_Bump1->setText(tr("关闭注射泵1"));
                        ui->Injuct_Bump2->setText(tr("关闭注射泵2"));
                        ui->Injuct_Bump3->setText(tr("关闭注射泵3"));
                        ui->Injuct_Bump4->setText(tr("关闭注射泵4"));
                        ui->Injuct_Bump5->setText(tr("关闭注射泵5"));
                        ui->Injuct_Bump6->setText(tr("关闭注射泵6"));
                        ui->Injuct_Bump7->setText(tr("关闭注射泵7"));
                        break;

                    default:
                        break;
                    }
                    break;

                case CMD_CODE_INJUCET_VOLUME1:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("泵1注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME2:
                   QMessageBox::warning(this,tr("温馨提醒"),tr("泵2注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME3:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("泵3注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME4:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("泵4注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME5:
                   QMessageBox::warning(this,tr("温馨提醒"),tr("泵5注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME6:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("泵6注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_VOLUME7:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("泵7注液量设置成功！"));
                    break;

                case CMD_CODE_INJUCET_TIME:
                    QMessageBox::warning(this,tr("温馨提醒"),tr("灌装时间设置成功！"));
                    break;

                    default:
                    break;
                 }
                 ReadBuff.clear();
            }
            else
            {
                ReadBuff.clear();
                return;
            }
        }
        else
        {
            ReadBuff.clear();
            return;
        }

    }
}

void MainWindow::on_L100_Switch_clicked()
{
    quint8 DATA = 0;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_OPEN,&DATA);
}

void MainWindow::on_Start_Appratus_clicked()
{
    quint8 DATA = 1;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_APPARATUS,&DATA);
}

void MainWindow::on_Exhaust_AIR_clicked()
{
    quint8 DATA = 0;
    if(ui->Exhaust_AIR->text()==tr("开始排空"))
    {
       DATA = 1;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_EXHAUST_AIR,&DATA);
    }
    else
    {
       DATA = 0;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_EXHAUST_AIR,&DATA);
    }
}

void MainWindow::on_RECYCLE_clicked()
{
    quint8 DATA = 0;
    if(ui->RECYCLE->text()==tr("回收磁珠"))
    {
       DATA = 1;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_RECYCLE,&DATA);
    }
    else
    {
       DATA = 0;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_RECYCLE,&DATA);
    }
}

void MainWindow::on_L100_INJECT_clicked()
{
    quint8 DATA = 0;
    if(ui->L100_INJECT->text()==tr("开始灌装"))
    {
       DATA = 1;
       CommandSend(1,CMD_TYPE_APP, CMD_CODE_INJECT,&DATA); 
    }
}

void MainWindow::on_Quit_clicked()
{
     this->close();
}

void MainWindow::on_Apparatus_Temp_clicked()
{
    quint8 DATA = 0;
    DATA = ui->Warm_Temp->text().toInt();
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_TEMP,&DATA);
}

void MainWindow::on_Apparatus_Time_clicked()
{
    quint8 DATA = 0;
    DATA = ui->Warm_Time->text().toInt();
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_TIME,&DATA);
}

void MainWindow::on_Control_Temp1_clicked()
{
    quint8 DATA = 0;
    if(ui->Control_Temp1->text()==tr("关闭加热块1"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BLOCK1,&DATA);
    }
    else
    {
        DATA = 1;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BLOCK1,&DATA);
    }
}

void MainWindow::on_Control_Temp2_clicked()
{
    quint8 DATA = 0;
    if(ui->Control_Temp2->text()==tr("关闭加热块2"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BLOCK2,&DATA);
    }
    else
    {
        DATA = 1;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BLOCK2,&DATA);
    }
}

void MainWindow::on_Open_Carve_clicked()
{
    quint8 DATA = 1;
    if(ui->Open_Carve->text()==tr("正向切割"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_CARVE_DIRECTION,&DATA);
    }
    else
    {
        DATA = 0;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_CARVE_DIRECTION,&DATA);
    }
}

void MainWindow::on_Close_Carve_clicked()
{
    quint8 DATA = 2;
    ui->Open_Carve->setText(tr("正向切割"));
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_CARVE_RESET,&DATA);
}

void MainWindow::on_Bumping_post1_clicked()
{
    quint8 DATA = 1;
    if(ui->Bumping_post1->text()==tr("打开加热挡柱"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BUMP,&DATA);
    }
    else
    {
        DATA = 0;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_WARM_BUMP,&DATA);
    }
}

void MainWindow::on_Bumping_post2_clicked()
{
    quint8 DATA = 1;
    if(ui->Bumping_post2->text()==tr("打开切割挡柱"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_CARVE_BUMP,&DATA);
    }
    else
    {
        DATA = 0;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_CARVE_BUMP,&DATA);
    }
}

void MainWindow::on_Debug_clicked()
{
    quint8 DATA = 0;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_DEBUG,&DATA);
}

void MainWindow::on_Normal_clicked()
{
//    quint8 DATA = 1;
//    CommandSend(1,CMD_TYPE_APP, CMD_CODE_NORMAL,&DATA);
}

void MainWindow::on_AIR_Cylinder1_clicked()
{
    quint8 DATA = 1;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_AIR_CYLINDER1,&DATA);
}

void MainWindow::on_AIR_Cylinder2_clicked()
{
    quint8 DATA = 1;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_AIR_CYLINDER2,&DATA);
}

void MainWindow::on_AIR_Cylinder3_clicked()
{
    quint8 DATA = 1;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_AIR_CYLINDER3,&DATA);
}

void MainWindow::on_AIR_Cylinder4_clicked()
{
    quint8 DATA = 1;
    CommandSend(1,CMD_TYPE_APP, CMD_CODE_AIR_CYLINDER4,&DATA);
}

void MainWindow::on_Injuct_Bump1_clicked()
{
    quint8 Buf[2] = {1,1};
    if(ui->Injuct_Bump1->text()==tr("打开注射泵1"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump2_clicked()
{
    quint8 Buf[2] = {2,1};
    if(ui->Injuct_Bump2->text()==tr("打开注射泵2"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump3_clicked()
{
    quint8 Buf[2] = {3,1};
    if(ui->Injuct_Bump3->text()==tr("打开注射泵3"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump4_clicked()
{
    quint8 Buf[2] = {4,1};
    if(ui->Injuct_Bump4->text()==tr("打开注射泵4"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump5_clicked()
{
    quint8 Buf[2] = {5,1};
    if(ui->Injuct_Bump5->text()==tr("打开注射泵5"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump6_clicked()
{
    quint8 Buf[2] = {6,1};
    if(ui->Injuct_Bump6->text()==tr("打开注射泵6"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump7_clicked()
{
    quint8 Buf[2] = {7,1};
    if(ui->Injuct_Bump7->text()==tr("打开注射泵7"))
    {
        CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
    else
    {
       Buf[1] = 0;
       CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
    }
}

void MainWindow::on_Injuct_Bump_Allopen_clicked()
{
    quint8 Buf[2] = {8,1};
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
}

void MainWindow::on_Injuct_Bump_Allclose_clicked()
{
    quint8 Buf[2] = {0,1};
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_BUMP,Buf);
}

void MainWindow::on_Set_Injuct_1_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_1->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME1,Buf);
}

void MainWindow::on_Set_Injuct_2_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_2->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME2,Buf);
}

void MainWindow::on_Set_Injuct_3_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_3->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME3,Buf);
}

void MainWindow::on_Set_Injuct_4_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_4->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME4,Buf);
}

void MainWindow::on_Set_Injuct_5_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_5->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME5,Buf);
}

void MainWindow::on_Set_Injuct_6_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_6->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME6,Buf);
}

void MainWindow::on_Set_Injuct_7_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Count_7->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_VOLUME7,Buf);
}

void MainWindow::on_Press_Plate_clicked()
{
    quint8 DATA = 1;
    if(ui->Press_Plate->text()==tr("压板下降"))
    {
      CommandSend(1,CMD_TYPE_APP, CMD_CODE_PRESS_PLATE,&DATA);
    }
    else
    {
        DATA = 0;
        CommandSend(1,CMD_TYPE_APP, CMD_CODE_PRESS_PLATE,&DATA);
    }
}

void MainWindow::on_Set_Injuct_time_clicked()
{
    quint16 DATA = 0;
    quint8 Buf[2] = {0};
    DATA = ui->Injuct_Time->text().toInt();
    memcpy(Buf,&DATA,2);
    CommandSend(2,CMD_TYPE_APP, CMD_CODE_INJUCET_TIME,Buf);
}
