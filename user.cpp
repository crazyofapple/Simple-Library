#include "user.h"
#include "ui_user.h"
#include <qmessagebox.h>
#include <vector>
#include <utility>
#include <QDebug>
#include "data.h"
#include "booker.h"
#include "myuser.h"
#include <QDateTime>
user::user(QWidget *parent) :QDialog(parent),ui(new Ui::user)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);

    ui->label_27->setVisible(false);

    ui->label_29->setVisible(false);

    ui->label_30->setVisible(false);

    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);
    ui->label_23->setText("");
    ui->label_24->setText("");

    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    ui->label1->setVisible(false);
    ui->label2->setVisible(false);
    ui->label3->setVisible(false);
    ui->label4->setVisible(false);
    ui->label5->setVisible(false);


}

void user::clear()
{
    ui->label001->setText("");
    ui->label002->setText("");
    ui->label003->setText("");
    ui->label004->setText("");
    ui->label005->setText("");

    ui->textEdit001->setText("");
    ui->textEdit002->setText("");
    ui->textEdit003->setText("");
    ui->textEdit004->setText("");
    ui->textEdit005->setText("");

    ui->textEdit0001->setText("");
    ui->textEdit0002->setText("");
    ui->textEdit0003->setText("");
    ui->textEdit0004->setText("");
    ui->textEdit0005->setText("");

    ui->label0001->setText("");
    ui->label0002->setText("");
    ui->label0003->setText("");
    ui->label0004->setText("");
    ui->label0005->setText("");

    ui->label00001->setText("");
    ui->label00002->setText("");
    ui->label00003->setText("");
    ui->label00004->setText("");
    ui->label00005->setText("");

    ui->pushButton01->setVisible(false);
    ui->pushButton02->setVisible(false);
    ui->pushButton03->setVisible(false);
    ui->pushButton04->setVisible(false);
    ui->pushButton05->setVisible(false);

    ui->pushButton01->setEnabled(false);
    ui->pushButton02->setEnabled(false);
    ui->pushButton03->setEnabled(false);
    ui->pushButton04->setEnabled(false);
    ui->pushButton05->setEnabled(false);
}
void user::onLoad()
{
    Datastore::Record**  record;
    QString s =ui->label_23->text();
    string str =  q2s(s);
    int uid = atoi(str.c_str());
    record = Booker::userIDFindRecord(uid);
    if(record == nullptr) {
        return;
    }
    qDebug("ok");
    printRecordList(record);
}
void user::receive(QString str)
{
    userName = str;//
   // qDebug("hello simida");
    ui->label_24->setText(userName);
    Datastore::User* usr = UserManager::SelectUser(q2s(str));
    userID=usr->ID;
    QString ss = QString::number(userID, 10);
    ui->label_23->setText(ss);
    ui->label_24->adjustSize();
    clear();

    onLoad();
}
user::~user()
{
    delete ui;
}


// 原密码判断
void user::on_lineEdit_4_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_4->text();
    string s = _trim(q2s(str));
    if (s.size()>0 && s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))){
        qDebug("%s", s.c_str());
        char Name[LEN_USER_NAME];
        strcpy(Name, q2s(userName).c_str());
        qDebug("%s",Name);
        auto user = Datastore::Select<Datastore::User>([&](const Datastore::User* user) {
            return !strcmp(user->userName, Name);
        });

        if (!strcmp(user->password, q2s(encrypt(s2q(s))).c_str())) {
            ui->label_27->setVisible(false);
        }else {
            ui->label_27->setVisible(true);
        }
    }else {
        ui->label_27->setVisible(true);
    }
}
// 新密码第一次判断
void user::on_lineEdit_5_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_5->text();
    string s = _trim(q2s(str));
    if (s.size()>0&&s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))){
        ui->label_29->setVisible(false);
    }else {
        ui->label_29->setVisible(true);
    }
}
// 新密码第二次验证
void user::on_lineEdit_6_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_6->text();
    string s = _trim(q2s(str));
    if (s.size()>0 && s.size()<LEN_USER_PASSWORD) {
        QString str2 = ui->lineEdit_5->text();
        string s2 = _trim(q2s(str2));
        if (s2.size()>0 && s2.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s2)) && s2 == s) {
            ui->label_30->setVisible(false);
        }else {
            ui->label_30->setVisible(true);
        }
    }
}

void user::on_pushButton_8_clicked()
{
    if (!ui->label_27->isVisible() && !ui->label_29->isVisible()
            && !ui->label_30->isVisible() && ui->lineEdit_5->text().size() > 0
                && ui->lineEdit_6->text().size() && ui->lineEdit_4->text().size() > 0) {
        if (UserManager::UpdataUserPassword(q2s(userName), _trim(q2s(ui->lineEdit_5->text())))) {
             QMessageBox::warning(this,tr("Success"),tr("change password success"),QMessageBox::Yes);
             ui->lineEdit_4->clear();
             ui->lineEdit_5->clear();
             ui->lineEdit_6->clear();
        }else {
             QMessageBox::warning(this,tr("Success"),tr("change password fail"),QMessageBox::Yes);
        }
    }else {
         QMessageBox::warning(this,tr("Success"),tr("input illegal"),QMessageBox::Yes);
    }
}

void user::on_pushButton_15_clicked()
{
    if(nowCnt >= newVt.size()){
        QMessageBox::warning(this,tr("Success"),tr("already last page"),QMessageBox::Yes);
        return;
    }
    prevRecordNum = nowRecordNum;
    clear();
    int ii = 0;
    int pre_x = nowCnt;
    while(nowCnt < newVt.size() && ii < 5) {
        int i = ii%5+1;

        string tmp0="label";tmp0+=(char)(i+'0');
        QLabel * label0=findChild<QLabel*>(s2q(tmp0));
        int ss=newVt[ii].first->ID;
        QString s2 = QString::number(ss, 10);
        label0->setText(s2);
        label0->adjustSize();

        string tmp1 ="label00";tmp1+=(char)(i+'0');
        //  string x1="";
        // x1 += newVt[ii].first->bookId;
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        QString sss = QString::number(nowCnt+1, 10);
        label1->setText(sss);
        label1->adjustSize();

        string tmp2 = "textEdit00";tmp2+=(char)(i+'0');
        string x2="";
        int tt=newVt[ii].first->bookId;
        x2+=Booker::IDFindBook(tt)->bookName;
        QTextEdit * textedit1 = findChild<QTextEdit*>(s2q(tmp2));
        textedit1->setText(s2q(x2));


        string tmp3 = "textEdit000";tmp3+=(char)(i+'0');
        string x3="";
        tt = newVt[ii].first->bookId;
        x3+=Booker::IDFindBook(tt)->bookAuthor;
        QTextEdit * textedit2 = findChild<QTextEdit*>(s2q(tmp3));
        textedit2->setText(s2q(x3));


        string tmp4 = "label000";tmp4+=(char)(i+'0');
        QString x4 = QDateTime::fromTime_t(newVt[ii].first->borrowTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label2 = findChild<QLabel*>(s2q(tmp4));
        label2->setText(x4);


        string tmp5 = "label0000";tmp5+=(char)(i+'0');
        QString x5 = QDateTime::fromTime_t(newVt[ii].first->returnTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label3 = findChild<QLabel*>(s2q(tmp5));
        label3->setText(x5);



        string tmp6 = "pushButton0";tmp6+=(char)(i+'0');
        QPushButton * pushbotton1 = findChild<QPushButton*>(s2q(tmp6));
        pushbotton1->setVisible(true);
        if(newVt[ii].first->isBorrowed && !newVt[ii].first->isRenew){//可续借
            pushbotton1->setEnabled(true);
            pushbotton1->setVisible(true);
        }
        else {
            pushbotton1->setVisible(false);
        }

        ii++;
        nowCnt++;
    }
    int now_x = nowCnt;
    nowRecordNum = now_x - pre_x;
}

void user::on_pushButton_2_clicked()
{
    if (prevRecordNum < 5) {
        QMessageBox::warning(this,tr("Success"),tr("already first page"),QMessageBox::Yes);
        return;
    }
    clear();
    nowRecordNum = 5;
    nowCnt -= nowRecordNum;
    nowCnt -= 5;
    if (nowCnt >= 5) prevRecordNum = 5;
    else prevRecordNum = nowCnt;
    int ii = 0;
    int pre_x = nowCnt;
    while(nowCnt < newVt.size() && ii < 5) {
        int i = ii%5+1;

        string tmp0="label";tmp0+=(char)(i+'0');
        QLabel * label0=findChild<QLabel*>(s2q(tmp0));
        int ss=newVt[ii].first->ID;
        QString s2 = QString::number(ss, 10);
        label0->setText(s2);
        label0->adjustSize();

        string tmp1 ="label00";tmp1+=(char)(i+'0');
        //  string x1="";
        // x1 += newVt[ii].first->bookId;
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        QString sss = QString::number(nowCnt+1, 10);
        label1->setText(sss);
        label1->adjustSize();

        string tmp2 = "textEdit00";tmp2+=(char)(i+'0');
        string x2="";
        int tt=newVt[ii].first->bookId;
        x2+=Booker::IDFindBook(tt)->bookName;
        QTextEdit * textedit1 = findChild<QTextEdit*>(s2q(tmp2));
        textedit1->setText(s2q(x2));


        string tmp3 = "textEdit000";tmp3+=(char)(i+'0');
        string x3="";
        tt = newVt[ii].first->bookId;
        x3+=Booker::IDFindBook(tt)->bookAuthor;
        QTextEdit * textedit2 = findChild<QTextEdit*>(s2q(tmp3));
        textedit2->setText(s2q(x3));


        string tmp4 = "label000";tmp4+=(char)(i+'0');
        QString x4 = QDateTime::fromTime_t(newVt[ii].first->borrowTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label2 = findChild<QLabel*>(s2q(tmp4));
        label2->setText(x4);


        string tmp5 = "label0000";tmp5+=(char)(i+'0');
        QString x5 = QDateTime::fromTime_t(newVt[ii].first->returnTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label3 = findChild<QLabel*>(s2q(tmp5));
        if (newVt[ii].first->borrowTime == newVt[ii].first->returnTime){
            label3->setText("borrowing");
        }else {
            label3->setText(x5);
            ;
        }


        string tmp6 = "pushButton0";tmp6+=(char)(i+'0');
        QPushButton * pushbotton1 = findChild<QPushButton*>(s2q(tmp6));
        pushbotton1->setVisible(true);
        if(newVt[ii].first->isBorrowed && !newVt[ii].first->isRenew){//可续借
            pushbotton1->setEnabled(true);
            pushbotton1->setVisible(true);
        }
        else {
            pushbotton1->setVisible(false);
        }

        ii++;
        nowCnt++;
    }
    int now_x = nowCnt;
    nowRecordNum = now_x - pre_x;
}

void user::on_pushButton01_clicked()
{
    QString s=ui->label1->text();
    int recordId=atoi(q2s(s).c_str());
    Datastore::Record* record=Booker::recordIDFindRecord(recordId);
    record->isRenew = true;
    if (Datastore::InsertOrUpdate(record) != -1){
        QMessageBox::warning(this,tr("Success"),tr("renew success"),QMessageBox::Yes);
    }else {
        QMessageBox::warning(this,tr("Success"),tr("renew error"),QMessageBox::Yes);
    }
    ui->pushButton01->setVisible(false);
    ui->pushButton01->setEnabled(false);
}

void user::on_pushButton02_clicked()
{
    QString s=ui->label2->text();
    int recordId=atoi(q2s(s).c_str());
    Datastore::Record* record=Booker::recordIDFindRecord(recordId);
    record->isRenew = true;
    if (Datastore::InsertOrUpdate(record) != -1){
        QMessageBox::warning(this,tr("Success"),tr("renew success"),QMessageBox::Yes);
    }else {
        QMessageBox::warning(this,tr("Success"),tr("renew error"),QMessageBox::Yes);
    }
    ui->pushButton02->setVisible(false);
    ui->pushButton02->setEnabled(false);
}

void user::on_pushButton03_clicked()
{
    QString s=ui->label3->text();
    int recordId=atoi(q2s(s).c_str());
    Datastore::Record* record=Booker::recordIDFindRecord(recordId);
    record->isRenew = true;
    if (Datastore::InsertOrUpdate(record) != -1){
        QMessageBox::warning(this,tr("Success"),tr("renew success"),QMessageBox::Yes);
    }else {
        QMessageBox::warning(this,tr("Success"),tr("renew error"),QMessageBox::Yes);
    }
    ui->pushButton03->setVisible(false);
    ui->pushButton03->setEnabled(false);
}

void user::on_pushButton04_clicked()
{
    QString s=ui->label4->text();
    int recordId=atoi(q2s(s).c_str());
    Datastore::Record* record=Booker::recordIDFindRecord(recordId);
    record->isRenew = true;
    if (Datastore::InsertOrUpdate(record) != -1){
        QMessageBox::warning(this,tr("Success"),tr("renew success"),QMessageBox::Yes);
    }else {
        QMessageBox::warning(this,tr("Success"),tr("renew error"),QMessageBox::Yes);
    }
    ui->pushButton04->setVisible(false);
    ui->pushButton04->setEnabled(false);
}

void user::on_pushButton05_clicked()
{
    QString s=ui->label5->text();
    int recordId=atoi(q2s(s).c_str());
    Datastore::Record* record=Booker::recordIDFindRecord(recordId);
    record->isRenew = true;
    if (Datastore::InsertOrUpdate(record) != -1){
        QMessageBox::warning(this,tr("Success"),tr("renew success"),QMessageBox::Yes);
    }else {
        QMessageBox::warning(this,tr("Success"),tr("renew error"),QMessageBox::Yes);
    }
    ui->pushButton05->setVisible(false);
    ui->pushButton05->setEnabled(false);
}
void user::printRecordList(Datastore::Record **list)
{
    int i = 0;
    newVt.clear();
    vt.clear();
     clear();
    prevRecordNum = nowRecordNum = -1;
    if(list[0] == NULL){
        QMessageBox::warning(this,tr("Success"),tr("NO DATA hahhaha"),QMessageBox::Yes);
        return;
    }

    while (list[i] != nullptr){
        vt.push_back(list[i]);
        i++;
    }
    for (auto i = vt.begin(); i != vt.end(); i++)
    {
        //for (; j != vt.end() && ((*i)->userId ==(*j)->userId); j++);
        newVt.push_back(make_pair(*i, 1));
    }

    qDebug("YESYEESSSS %d %d",vt.size(), newVt.size());
    int ii = 0;
    nowCnt = 0;
    while(ii < newVt.size() && ii < 5){
        int i = ii%5+1;

        string tmp0="label";
        tmp0+=(char)(i+'0');
        qDebug("%s",tmp0.c_str());
        QLabel * label0=this->findChild<QLabel*>(s2q(tmp0));
        int ss=newVt[ii].first->ID;
        QString s2 = QString::number(ss, 10);
        label0->setText(s2);
        label0->adjustSize();
        qDebug("ok + ok");
        string tmp1 ="label00";
        tmp1+=(char)(i+'0');
        QLabel * label1 = findChild<QLabel*>(s2q(tmp1));
        QString sss = QString::number(nowCnt+1, 10);
        label1->setText(sss);
        label1->adjustSize();

        string tmp2 = "textEdit00";
        tmp2+=(char)(i+'0');
        string x2="";
        int tt=newVt[ii].first->bookId;
        x2+=Booker::IDFindBook(tt)->bookName;
        QTextEdit * textedit1 = findChild<QTextEdit*>(s2q(tmp2));
        textedit1->setText(s2q(x2));


        string tmp3 = "textEdit000";
        string x3="";
        tmp3+=(char)(i+'0');
        tt = newVt[ii].first->bookId;
         x3+=Booker::IDFindBook(tt)->bookAuthor;
        QTextEdit * textedit2 = findChild<QTextEdit*>(s2q(tmp3));
        textedit2->setText(s2q(x3));


        string tmp4 = "label000";
        tmp4+=(char)(i+'0');
        QString x4 = QDateTime::fromTime_t(newVt[ii].first->borrowTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label2 = findChild<QLabel*>(s2q(tmp4));
        label2->setText(x4);


        string tmp5 = "label0000";
        tmp5+=(char)(i+'0');
        QString x5 = QDateTime::fromTime_t(newVt[ii].first->returnTime).toUTC().toString("yyyy-MM-dd");
        QLabel * label3 = findChild<QLabel*>(s2q(tmp5));
        if (newVt[ii].first->borrowTime == newVt[ii].first->returnTime){
            label3->setText("borrowing");
        }else {
            label3->setText(x5);
            ;
        }




        string tmp6 = "pushButton0";
        tmp6+=(char)(i+'0');
       QPushButton * pushbotton1 = findChild<QPushButton*>(s2q(tmp6));
       pushbotton1->setVisible(true);
       if(newVt[ii].first->isBorrowed && !newVt[ii].first->isRenew){//可续借
           pushbotton1->setEnabled(true);
           pushbotton1->setVisible(true);
       }
       else {
           pushbotton1->setVisible(false);
       }
        ii++;
        nowCnt++;
    }
    nowRecordNum = nowCnt;
}
