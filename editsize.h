#ifndef EDITSIZE_H
#define EDITSIZE_H

#include <QDialog>

namespace Ui {
class EditSize;
}

class EditSize : public QDialog
{
    Q_OBJECT

public:
    explicit EditSize(QWidget *parent = 0);
    ~EditSize();
    int ReturnEditSize();
    void SetEditSize(int size);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EditSize *ui;
};

#endif // EDITSIZE_H
