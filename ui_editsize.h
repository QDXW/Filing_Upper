/********************************************************************************
** Form generated from reading UI file 'editsize.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITSIZE_H
#define UI_EDITSIZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditSize
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *EditSize)
    {
        if (EditSize->objectName().isEmpty())
            EditSize->setObjectName(QStringLiteral("EditSize"));
        EditSize->resize(719, 441);
        lineEdit = new QLineEdit(EditSize);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(340, 110, 291, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font.setPointSize(32);
        lineEdit->setFont(font);
        pushButton = new QPushButton(EditSize);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 300, 231, 111));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font1.setPointSize(28);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(EditSize);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 300, 221, 111));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(EditSize);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(false);
        pushButton_3->setGeometry(QRect(80, 110, 231, 101));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(28);
        pushButton_3->setFont(font2);

        retranslateUi(EditSize);

        QMetaObject::connectSlotsByName(EditSize);
    } // setupUi

    void retranslateUi(QDialog *EditSize)
    {
        EditSize->setWindowTitle(QApplication::translate("EditSize", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("EditSize", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("EditSize", "\345\217\226\346\266\210", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("EditSize", "\346\263\250\346\266\262\351\207\217/ul", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EditSize: public Ui_EditSize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITSIZE_H
