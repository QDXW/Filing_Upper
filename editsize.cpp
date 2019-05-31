#include "editsize.h"
#include "ui_editsize.h"

EditSize::EditSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSize)
{
    ui->setupUi(this);
}

EditSize::~EditSize()
{
    delete ui;
}

void EditSize::on_pushButton_clicked()
{
    emit QDialog::accept();
}
int EditSize::ReturnEditSize()
{
    return ui->lineEdit->text().toInt();
}
void EditSize::SetEditSize(int size)
{
    ui->lineEdit->setFocus();
    ui->lineEdit->setText(tr("%1").arg(size));
}

void EditSize::on_pushButton_2_clicked()
{
    emit QDialog::reject();
}
