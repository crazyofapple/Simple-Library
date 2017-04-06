#ifndef usermanager_H
#define usermanager_H
#include"data.h"
#include<QDialog>
#include<QWidget>
#include "ui_usermanager.h"
namespace Ui {
class usermanager;
}

class usermanager : public QDialog
{
    Q_OBJECT
    
public:
    explicit usermanager(QWidget *parent = 0);
    ~usermanager();
    void clear();
    void myshow();
    void printRecordList(Datastore::Record **list);
private slots:

    void on_pushButton_1_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_30_clicked();

    void on_lineEdit_22_textChanged(const QString &arg1);

    void on_lineEdit_25_textChanged(const QString &arg1);

    void on_lineEdit_28_textChanged(const QString &arg1);

private:
    Ui::usermanager *ui;
    int ID;
};

#endif // usermanager_H
