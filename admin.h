#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "data.h"
#include <string>
#include <QMessageBox>
#include "myuser.h"
#include "bookmanager.h"
#include "usermanager.h"
namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT
    
public:
    explicit admin(QWidget *parent = 0);
    ~admin();
    
signals:
    void jumpback();

private slots:
    void on_lineEdit_01_textChanged(const QString &arg1);

    void on_lineEdit_02_textChanged(const QString &arg1);

    void on_lineEdit_03_textChanged(const QString &arg1);

    void receive(QString);
    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_test_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::admin *ui;
    QString userName;
    QString userInfo;
    bookManager  bookmanager;
    int timerId;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // ADMIN_H
