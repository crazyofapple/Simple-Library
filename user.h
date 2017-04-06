#ifndef USER_H
#define USER_H
#include <QDialog>
#include "data.h"
#include "booker.h"
#include "bookimformation.h"

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = 0);
    void printRecordList(Datastore::Record **list);
    ~user();
    void onLoad();
    void clear();
private slots:
    void receive(QString);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton01_clicked();

    void on_pushButton02_clicked();

    void on_pushButton03_clicked();

    void on_pushButton04_clicked();

    void on_pushButton05_clicked();

private:
    Ui::user *ui;
    QString userName;
    int userID;
    vector<Datastore::Record *> vt;
    vector<pair<Datastore::Record *,int> > newVt;
    int nowCnt;
    int prevRecordNum, nowRecordNum;
    //bookImformation * bookinformation;
};

#endif // USER_H
