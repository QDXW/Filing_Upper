/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *TypeSelctcomboBox;
    QPushButton *Connect_Btn;
    QComboBox *COMSelectcomboBox;
    QPushButton *Quit;
    QGroupBox *groupBox;
    QPushButton *Set_Injuct_M;
    QPushButton *Set_Injuct_R2;
    QPushButton *Set_Injuct_W;
    QLineEdit *Injuct_Count_R2;
    QLineEdit *Injuct_Count_W;
    QLineEdit *Injuct_Count_M;
    QLineEdit *Injuct_Count_R1;
    QPushButton *Set_Injuct_R1;
    QGroupBox *groupBox_Filling;
    QPushButton *L100_Filling;
    QGroupBox *groupBox_Padding;
    QPushButton *Padding;
    QGroupBox *groupBox_Wash_All;
    QPushButton *PUMP_WASH_All;
    QGroupBox *groupBox_Wash;
    QPushButton *PUMP_WASH;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1920, 1200);
        MainWindow->setMinimumSize(QSize(1920, 1200));
        MainWindow->setMaximumSize(QSize(1920, 1200));
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TypeSelctcomboBox = new QComboBox(centralWidget);
        TypeSelctcomboBox->setObjectName(QStringLiteral("TypeSelctcomboBox"));
        TypeSelctcomboBox->setGeometry(QRect(590, 10, 161, 81));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TypeSelctcomboBox->sizePolicy().hasHeightForWidth());
        TypeSelctcomboBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(18);
        TypeSelctcomboBox->setFont(font);
        TypeSelctcomboBox->setStyleSheet(QStringLiteral(""));
        Connect_Btn = new QPushButton(centralWidget);
        Connect_Btn->setObjectName(QStringLiteral("Connect_Btn"));
        Connect_Btn->setGeometry(QRect(280, 10, 231, 81));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Connect_Btn->sizePolicy().hasHeightForWidth());
        Connect_Btn->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(26);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        Connect_Btn->setFont(font1);
        Connect_Btn->setStyleSheet(QStringLiteral(""));
        COMSelectcomboBox = new QComboBox(centralWidget);
        COMSelectcomboBox->setObjectName(QStringLiteral("COMSelectcomboBox"));
        COMSelectcomboBox->setGeometry(QRect(20, 10, 201, 81));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(20);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(COMSelectcomboBox->sizePolicy().hasHeightForWidth());
        COMSelectcomboBox->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(30);
        COMSelectcomboBox->setFont(font2);
        COMSelectcomboBox->setStyleSheet(QStringLiteral(""));
        COMSelectcomboBox->setIconSize(QSize(50, 50));
        Quit = new QPushButton(centralWidget);
        Quit->setObjectName(QStringLiteral("Quit"));
        Quit->setGeometry(QRect(80, 1010, 401, 181));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font3.setPointSize(52);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        Quit->setFont(font3);
        Quit->setStyleSheet(QStringLiteral(""));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 140, 1851, 451));
        Set_Injuct_M = new QPushButton(groupBox);
        Set_Injuct_M->setObjectName(QStringLiteral("Set_Injuct_M"));
        Set_Injuct_M->setGeometry(QRect(90, 280, 381, 151));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font4.setPointSize(32);
        Set_Injuct_M->setFont(font4);
        Set_Injuct_M->setStyleSheet(QStringLiteral(""));
        Set_Injuct_R2 = new QPushButton(groupBox);
        Set_Injuct_R2->setObjectName(QStringLiteral("Set_Injuct_R2"));
        Set_Injuct_R2->setGeometry(QRect(980, 30, 351, 151));
        Set_Injuct_R2->setFont(font4);
        Set_Injuct_R2->setStyleSheet(QStringLiteral(""));
        Set_Injuct_W = new QPushButton(groupBox);
        Set_Injuct_W->setObjectName(QStringLiteral("Set_Injuct_W"));
        Set_Injuct_W->setGeometry(QRect(980, 280, 361, 151));
        Set_Injuct_W->setFont(font4);
        Set_Injuct_W->setStyleSheet(QStringLiteral(""));
        Injuct_Count_R2 = new QLineEdit(groupBox);
        Injuct_Count_R2->setObjectName(QStringLiteral("Injuct_Count_R2"));
        Injuct_Count_R2->setEnabled(false);
        Injuct_Count_R2->setGeometry(QRect(1370, 60, 241, 121));
        QFont font5;
        font5.setFamily(QStringLiteral("Times New Roman"));
        font5.setPointSize(38);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        Injuct_Count_R2->setFont(font5);
        Injuct_Count_R2->setStyleSheet(QStringLiteral(""));
        Injuct_Count_W = new QLineEdit(groupBox);
        Injuct_Count_W->setObjectName(QStringLiteral("Injuct_Count_W"));
        Injuct_Count_W->setEnabled(false);
        Injuct_Count_W->setGeometry(QRect(1370, 320, 241, 111));
        QFont font6;
        font6.setFamily(QStringLiteral("Times New Roman"));
        font6.setPointSize(38);
        Injuct_Count_W->setFont(font6);
        Injuct_Count_W->setStyleSheet(QStringLiteral(""));
        Injuct_Count_M = new QLineEdit(groupBox);
        Injuct_Count_M->setObjectName(QStringLiteral("Injuct_Count_M"));
        Injuct_Count_M->setEnabled(false);
        Injuct_Count_M->setGeometry(QRect(520, 310, 251, 121));
        Injuct_Count_M->setFont(font6);
        Injuct_Count_M->setStyleSheet(QStringLiteral(""));
        Injuct_Count_R1 = new QLineEdit(groupBox);
        Injuct_Count_R1->setObjectName(QStringLiteral("Injuct_Count_R1"));
        Injuct_Count_R1->setEnabled(false);
        Injuct_Count_R1->setGeometry(QRect(520, 60, 251, 121));
        Injuct_Count_R1->setBaseSize(QSize(0, 0));
        Injuct_Count_R1->setFont(font5);
        Injuct_Count_R1->setStyleSheet(QStringLiteral(""));
        Set_Injuct_R1 = new QPushButton(groupBox);
        Set_Injuct_R1->setObjectName(QStringLiteral("Set_Injuct_R1"));
        Set_Injuct_R1->setGeometry(QRect(90, 30, 371, 151));
        Set_Injuct_R1->setFont(font4);
        Set_Injuct_R1->setStyleSheet(QStringLiteral(""));
        groupBox_Filling = new QGroupBox(centralWidget);
        groupBox_Filling->setObjectName(QStringLiteral("groupBox_Filling"));
        groupBox_Filling->setGeometry(QRect(620, 700, 611, 421));
        L100_Filling = new QPushButton(groupBox_Filling);
        L100_Filling->setObjectName(QStringLiteral("L100_Filling"));
        L100_Filling->setGeometry(QRect(30, 30, 551, 361));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font7.setPointSize(62);
        font7.setBold(false);
        font7.setItalic(false);
        font7.setWeight(50);
        L100_Filling->setFont(font7);
        L100_Filling->setFocusPolicy(Qt::ClickFocus);
        L100_Filling->setStyleSheet(QStringLiteral(""));
        L100_Filling->setCheckable(false);
        L100_Filling->setAutoRepeat(false);
        L100_Filling->setAutoRepeatDelay(1);
        L100_Filling->setAutoRepeatInterval(1);
        L100_Filling->setAutoDefault(false);
        L100_Filling->setFlat(false);
        groupBox_Padding = new QGroupBox(centralWidget);
        groupBox_Padding->setObjectName(QStringLiteral("groupBox_Padding"));
        groupBox_Padding->setGeometry(QRect(70, 700, 411, 191));
        Padding = new QPushButton(groupBox_Padding);
        Padding->setObjectName(QStringLiteral("Padding"));
        Padding->setGeometry(QRect(10, 10, 391, 171));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font8.setPointSize(30);
        Padding->setFont(font8);
        Padding->setStyleSheet(QStringLiteral(""));
        groupBox_Wash_All = new QGroupBox(centralWidget);
        groupBox_Wash_All->setObjectName(QStringLiteral("groupBox_Wash_All"));
        groupBox_Wash_All->setGeometry(QRect(1340, 940, 411, 181));
        PUMP_WASH_All = new QPushButton(groupBox_Wash_All);
        PUMP_WASH_All->setObjectName(QStringLiteral("PUMP_WASH_All"));
        PUMP_WASH_All->setGeometry(QRect(10, 10, 391, 161));
        PUMP_WASH_All->setFont(font8);
        PUMP_WASH_All->setStyleSheet(QStringLiteral(""));
        groupBox_Wash = new QGroupBox(centralWidget);
        groupBox_Wash->setObjectName(QStringLiteral("groupBox_Wash"));
        groupBox_Wash->setGeometry(QRect(1340, 700, 411, 181));
        PUMP_WASH = new QPushButton(groupBox_Wash);
        PUMP_WASH->setObjectName(QStringLiteral("PUMP_WASH"));
        PUMP_WASH->setGeometry(QRect(10, 10, 391, 161));
        PUMP_WASH->setFont(font8);
        PUMP_WASH->setStyleSheet(QStringLiteral(""));
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(TypeSelctcomboBox, Connect_Btn);
        QWidget::setTabOrder(Connect_Btn, COMSelectcomboBox);
        QWidget::setTabOrder(COMSelectcomboBox, Quit);
        QWidget::setTabOrder(Quit, PUMP_WASH);
        QWidget::setTabOrder(PUMP_WASH, Set_Injuct_M);
        QWidget::setTabOrder(Set_Injuct_M, Set_Injuct_R2);
        QWidget::setTabOrder(Set_Injuct_R2, Set_Injuct_W);
        QWidget::setTabOrder(Set_Injuct_W, Injuct_Count_R2);
        QWidget::setTabOrder(Injuct_Count_R2, Injuct_Count_W);
        QWidget::setTabOrder(Injuct_Count_W, Injuct_Count_M);
        QWidget::setTabOrder(Injuct_Count_M, Injuct_Count_R1);
        QWidget::setTabOrder(Injuct_Count_R1, Set_Injuct_R1);

        retranslateUi(MainWindow);

        L100_Filling->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RL-A2000-Test", Q_NULLPTR));
        TypeSelctcomboBox->clear();
        TypeSelctcomboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "L100", Q_NULLPTR)
        );
        Connect_Btn->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        Quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        groupBox->setTitle(QString());
        Set_Injuct_M->setText(QApplication::translate("MainWindow", "M\346\263\250\346\266\262\351\207\217", Q_NULLPTR));
        Set_Injuct_R2->setText(QApplication::translate("MainWindow", "R2\346\263\250\346\266\262\351\207\217", Q_NULLPTR));
        Set_Injuct_W->setText(QApplication::translate("MainWindow", "W/B\346\263\250\346\266\262\351\207\217", Q_NULLPTR));
        Injuct_Count_R2->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        Injuct_Count_W->setText(QApplication::translate("MainWindow", "300", Q_NULLPTR));
        Injuct_Count_M->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        Injuct_Count_R1->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        Set_Injuct_R1->setText(QApplication::translate("MainWindow", "R1\346\263\250\346\266\262\351\207\217", Q_NULLPTR));
        groupBox_Filling->setTitle(QString());
        L100_Filling->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\201\214\350\243\205", Q_NULLPTR));
        groupBox_Padding->setTitle(QString());
        Padding->setText(QApplication::translate("MainWindow", "\346\270\205\346\264\227\346\266\262\345\241\253\345\205\205", Q_NULLPTR));
        groupBox_Wash_All->setTitle(QString());
        PUMP_WASH_All->setText(QApplication::translate("MainWindow", "\345\205\250\351\203\250\346\270\205\346\264\227", Q_NULLPTR));
        groupBox_Wash->setTitle(QString());
        PUMP_WASH->setText(QApplication::translate("MainWindow", "R1 R2 M\346\270\205\346\264\227", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
