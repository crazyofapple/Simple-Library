#include "usermanager.h"
#include "ui_usermanager.h"
#include <QMessageBox>
#include <QDialog>
#include "myuser.h"
#include "data.h"
usermanager::usermanager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usermanager)
{
    ui->setupUi(this);
    ui->lineEdit_22->setEchoMode(QLineEdit::Password);
    ui->lineEdit_25->setEchoMode(QLineEdit::Password);
    ui->lineEdit_28->setEchoMode(QLineEdit::Password);
    clear();
    ui->label_21->setVisible(false);
}

usermanager::~usermanager()
{
    delete ui;
}
void usermanager::clear() {
    ui->label_3->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->label_29->setVisible(false);
    ui->lineEdit_22->setVisible(false);
    ui->lineEdit_25->setVisible(false);
    ui->lineEdit_28->setVisible(false);
    ui->pushButton_30->setVisible(false);
    ui->pushButton_14->setVisible(false);
    ui->pushButton_15->setVisible(false);
    ui->pushButton_31->setVisible(false);
    ui->pushButton_14->setEnabled(true);
    ui->pushButton_15->setEnabled(true);
}
void usermanager::myshow(){
    ui->label_21->setVisible(true);
    ui->lineEdit_22->clear();
    ui->lineEdit_22->setVisible(true);
    ui->label_23->setVisible(false);

    ui->label_24->setVisible(true);
    ui->lineEdit_25->clear();
    ui->lineEdit_25->setVisible(true);
    ui->label_26->setVisible(false);

    ui->label_27->setVisible(true);
    ui->lineEdit_28->clear();
    ui->lineEdit_28->setVisible(true);
    ui->label_29->setVisible(false);

    ui->pushButton_30->setVisible(true);
    ui->pushButton_31->setVisible(true);
    //互斥
    ui->pushButton_14->setEnabled(false);
    ui->pushButton_15->setEnabled(false);
}

void usermanager::on_pushButton_1_clicked()
{
    clear();
    QString s = ui->lineEdit_1->text();
    string str = _trim(q2s(s));
    if (str.length() == 0) {
        QMessageBox::warning(this,tr("Success"),tr("no letter input"),QMessageBox::Yes);
        ui->lineEdit_1->clear();
        return;
    }
    qDebug("%s", str.c_str());
    if (isEmailAddress(s) == false) {
        QMessageBox::warning(this,tr("Success"),tr("illegal input"),QMessageBox::Yes);
        ui->lineEdit_1->clear();
        return;
    }

    Datastore::User*  user = UserManager::SelectUser(str);

    if (user == nullptr) {
        ui->label_3->setVisible(true);
    }else {
        ui->label_11->setVisible(true);
        ui->label_12->setVisible(true);
        ui->label_13->setVisible(true);
        ui->pushButton_14->setVisible(true);
        ui->pushButton_15->setVisible(true);
        ui->label_3->setVisible(false);
        ui->label_11->setText(s2q(user->userName));
        ui->label_12->setText(s2q(user->type));
        ui->label_13->setText(s2q(user->info));
        ui->label_11->adjustSize();
        ui->label_12->adjustSize();
        ui->label_13->adjustSize();
    }
}

void usermanager::on_pushButton_14_clicked()
{
    myshow();
}

void usermanager::on_pushButton_31_clicked()
{
    ui->label_21->setVisible(false);
    ui->lineEdit_22->clear();
    ui->lineEdit_22->setVisible(false);
    ui->label_23->setVisible(false);

    ui->label_24->setVisible(false);
    ui->lineEdit_25->clear();
    ui->lineEdit_25->setVisible(false);
    ui->label_26->setVisible(false);

    ui->label_27->setVisible(false);
    ui->lineEdit_28->clear();
    ui->lineEdit_28->setVisible(false);
    ui->label_29->setVisible(false);

    ui->pushButton_30->setVisible(false);
    ui->pushButton_31->setVisible(false);
    //互斥
    ui->pushButton_14->setEnabled(true);
    ui->pushButton_15->setEnabled(true);
}

void usermanager::on_pushButton_15_clicked()
{
    QMessageBox message(QMessageBox::Warning,"Information","Really to delete this user?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        if (UserManager::DeleteUser(q2s(ui->label_11->text()))) {
            QMessageBox::warning(this,tr("Success"),tr("delete ok"),QMessageBox::Yes);
            on_pushButton_1_clicked();
        }else {
            QMessageBox::warning(this,tr("Success"),tr("delete error"),QMessageBox::Yes);
        }
    }
    else
    {
        // do nothing
    }
}

void usermanager::on_pushButton_30_clicked()
{
    if (!ui->label_23->isVisible() && !ui->label_26->isVisible()
            && !ui->label_26->isVisible() && ui->lineEdit_22->text().size() > 0
                && ui->lineEdit_25->text().size() && ui->lineEdit_28->text().size() > 0) {
        if (UserManager::UpdataUserPassword(q2s(ui->label_11->text()), _trim(q2s(ui->lineEdit_25->text())))) {
             QMessageBox::warning(this,tr("Success"),tr("change password success"),QMessageBox::Yes);
             ui->label_21->setVisible(false);
             ui->lineEdit_22->clear();
             ui->lineEdit_22->setVisible(false);
             ui->label_23->setVisible(false);

             ui->label_24->setVisible(false);
             ui->lineEdit_25->clear();
             ui->lineEdit_25->setVisible(false);
             ui->label_26->setVisible(false);

             ui->label_27->setVisible(false);
             ui->lineEdit_28->clear();
             ui->lineEdit_28->setVisible(false);
             ui->label_29->setVisible(false);

             ui->pushButton_30->setVisible(false);
             ui->pushButton_31->setVisible(false);
             //互斥
             ui->pushButton_14->setEnabled(true);
             ui->pushButton_15->setEnabled(true);
        }else {
             QMessageBox::warning(this,tr("Success"),tr("change password fail"),QMessageBox::Yes);
        }
    }else {
         QMessageBox::warning(this,tr("Success"),tr("input illegal"),QMessageBox::Yes);
    }
}

void usermanager::on_lineEdit_22_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_22->text();
    string s = _trim(q2s(str));
    if (s.size()>0 && s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))){
        qDebug("%s", s.c_str());
        char Name[LEN_USER_NAME];
        strcpy(Name, q2s(ui->label_11->text()).c_str());
        qDebug("%s",Name);
        auto user = Datastore::Select<Datastore::User>([&](const Datastore::User* user) {
            return !strcmp(user->userName, Name);
        });
        if (!strcmp(user->password, q2s(encrypt(s2q(s))).c_str())) {
            ui->label_23->setVisible(false);
        }else {
            ui->label_23->setVisible(true);
        }
    }else {
        ui->label_23->setVisible(true);
    }
}
// 第一次密码
void usermanager::on_lineEdit_25_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_25->text();
    string s = _trim(q2s(str));
    if (s.size()>0&&s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))){
        ui->label_26->setVisible(false);
    }else {
        ui->label_26->setVisible(true);
    }
}
// 第二次密码
void usermanager::on_lineEdit_28_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_28->text();
    string s = _trim(q2s(str));
    if (s.size()>0 && s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))) {
        QString str2 = ui->lineEdit_25->text();
        string s2 = _trim(q2s(str2));
        if (s2.size()>0 && s2.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s2)) && s2 == s) {
            ui->label_29->setVisible(false);
        }else {
            ui->label_29->setVisible(true);
        }
    }
}
