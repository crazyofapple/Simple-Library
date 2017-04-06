#include "regist.h"
#include "ui_regist.h"
#include "data.h"
#include <qmessagebox.h>
regist::regist(QWidget *parent) :
    QDialog(parent),
    reg_ui(new Ui::regist)
{
    reg_ui->setupUi(this);
    reg_ui->logkey->setEchoMode(QLineEdit::Password);
    reg_ui->logkeysure->setEchoMode(QLineEdit::Password);
    //connect(this,SIGNAL(closing()),parent,SLOT(showagain()));
    //connect(reg_ui->exit2Login, SIGNAL(clicked()), ui, SLOT(show()));
    reg_ui->logid->setFocus();
    //reg_ui->exitb->setFlat(true);//无边框
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground, true);//透明
}

regist::~regist()
{
    delete reg_ui;
}

void regist::on_regb_clicked()
{
    QString userName = reg_ui->logid->text();
    QString password = reg_ui->logkey->text();
    QString password4sure = reg_ui->logkeysure->text();
    QString info = reg_ui->info->toPlainText();



    if(!isLegalInfo(info))
        reg_ui->waring5->setText(s2q("User information cannot exceed 20 characters."));
    if (isEmailAddress(userName) && isLegalPassword(password) && password == password4sure && isLegalInfo(info)) {
        if (InsertUser(userName, password, info)) {
            QMessageBox::warning(this,tr("Success"),tr("Successful registration."),QMessageBox::Yes);
            // to some page
        }else {
        reg_ui->waring5->setText(s2q("admin have"));
        }
    }else {
        QMessageBox::warning(this,tr("Warning"),tr("注册失败，请正确填写信息"),QMessageBox::Yes);
        //reg_ui->info->clear();
        //reg_ui->logid->clear();
        //reg_ui->logkey->clear();
        //reg_ui->logkeysure->clear();
    }
}
bool regist::InsertUser(QString Name, QString Password, QString Info) {
    char name[LEN_USER_NAME];
    char password[LEN_USER_PASSWORD];
    char info[LEN_USER_INFO];
    strcpy(name, Name.toStdString().c_str());
    strcpy(password, encrypt(Password).toStdString().c_str());
    strcpy(info, Info.toStdString().c_str());
    auto TemporaryUser = Datastore::Select<Datastore::User>([&](const Datastore::User* user){
        return !strcmp(name, user->userName);
    });
    if (TemporaryUser != NULL)
    {
        delete TemporaryUser;
        TemporaryUser = NULL;
        return false;
    }
    else
    {
        auto user = Datastore::Create<Datastore::User>();
        char type[LEN_USER_TYPE] = "user";
        strcpy(user->userName, name);
        strcpy(user->password, password);
        strcpy(user->info, info);
        strcpy(user->type, type);
        user->isDeleted = false;
        Datastore::InsertOrUpdate(user);
        delete user;
        user = NULL;
        delete TemporaryUser;
        TemporaryUser = NULL;
        TemporaryUser = Datastore::Select<Datastore::User>([&](const Datastore::User* user){
            return !strcmp(user->userName, name);
        });
        if (TemporaryUser != NULL)
        {
            delete TemporaryUser;
            TemporaryUser = NULL;
            return true;
        }
        else
        {
            delete TemporaryUser;
            TemporaryUser = NULL;
            return false;
        }
    }
}

void regist::on_exit2Login_clicked()
{
    close();
}

void regist::on_logid_editingFinished()
{
    QString userName = reg_ui->logid->text();
    if(!isEmailAddress(userName))
        reg_ui->waring5->setText(s2q("Please enter a valid email format."));
}

void regist::on_logkey_editingFinished()
{
    QString password = reg_ui->logkey->text();
    if(!isLegalPassword(password))
        reg_ui->waring5->setText(s2q("Please enter the 4-10 letter."));
}

void regist::on_logkeysure_editingFinished()
{
    QString password = reg_ui->logkey->text();
    QString password4sure = reg_ui->logkeysure->text();
    if(password != password4sure)
        reg_ui->waring5->setText(s2q("The two input password does not match"));
}
