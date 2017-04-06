#include "login.h"
#include "ui_login.h"
#include "data.h"
#include "regist.h"
#include <QMessageBox.h>
QString _Type;
Datastore::User * IUser;

login::login(QWidget *parent) :
    QDialog(parent),
    log_ui(new Ui::login)
{
    log_ui->setupUi(this);
    log_ui->logkey->setEchoMode(QLineEdit::Password);
    //ui->regbutton->setFlat(true);//无边框
    //setWindowFlags(Qt::FramelessWindowHint);
     //this->setAttribute(Qt::WA_TranslucentBackground, true);//透明
    Admin = new admin(this);
    Admin->hide();
    User = new user(this);
    User->hide();
    connect(this,SIGNAL(send(QString)),Admin,SLOT(receive(QString)));
    connect(this,SIGNAL(send2(QString)),User,SLOT(receive(QString)));
    connect(this,SIGNAL(closing()),parent,SLOT(showagain()));
}

login::~login()
{
    delete log_ui;
}

void login::jumptoindex(){
    emit closing();
    this->close();
}

bool login::getVerify(QString Name, QString Password) {
    if (Name.length() == 0)
        {
            log_ui->waring4->setText(s2q("user name should not be empty."));
            return false;
    }
    if (!isEmailAddress(Name)) {
        log_ui->waring4->setText(s2q("Please enter a valid email format,for example:###@###.###"));
        return false;
    }
    if (Password.length() == 0)
        {log_ui->waring4->setText(s2q("Password should not be empty"));return false;}

    if (!isLegalPassword(Password)) {
        log_ui->waring4->setText(s2q("Please enter the 4-10 letter"));
        return false;
    }
    return true;
}

void login::on_logbutton_clicked(){
    QString userName = log_ui->logid->text();
    QString password = log_ui->logkey->text();
    getVerify(userName,password);
    Login(userName,password);
        //QMessageBox::warning(this,tr("Success"),tr("login failed"),QMessageBox::Yes);
    if (getVerify(userName, password) && Login(userName, password)) {
        QMessageBox::warning(this,tr("恭喜您！"),tr("登陆成功"),QMessageBox::Yes);
        //hide();
        if (_Type == "admin") {
            qDebug("ok yamida");
            emit send(log_ui->logid->text());
            Admin->show();
        }else {
            emit send2(log_ui->logid->text());
            User->show();
        }
        log_ui->logid->clear();
        log_ui->logkey->clear();
    }else {
        QMessageBox::warning(this,tr("Warning"),tr("登陆失败"),QMessageBox::Yes);
        //如果不正确，弹出警告对话框
        //log_ui->logid->clear();//清空用户名输入框
        //log_ui->logkey->clear();//清空密码输入框
        //log_ui->logid->setFocus();//将光标转到用户名输入框
        //log_ui->waring4->clear();
    }
}

void login::on_regbutton_clicked(){
    reg=new regist(this);
    reg->exec();
}

void login::on_exitbutton_clicked()
{
    emit closing();
    reject();
}

bool login::Login(QString Name, QString Password) {
    IUser = new Datastore::User;
    char name[LEN_USER_NAME];
    char password[LEN_USER_PASSWORD];
    strcpy(name, Name.toStdString().c_str());
    strcpy(password, encrypt(Password).toStdString().c_str());
    strcpy(IUser->userName, name);
    auto user = Datastore::Select<Datastore::User>([&](const Datastore::User* user) {
        return !strcmp(user->userName,name);
    });

    if (user == NULL){
        log_ui->waring4->setText(s2q("User does not exist."));
        return false;
    }
    bool flag = strcmp(user->password, password) == 0;

    if (flag){
        _Type = user->type;
        IUser->ID = user->ID;
        IUser->isDeleted = user->isDeleted;
        strcpy(IUser->info, user->info);
        strcpy(IUser->password, user->password);
        strcpy(IUser->type, user->type);
        delete user;
        user = NULL;
        log_ui->waring4->setText("");
        return true;
    }else {
        strcpy(IUser->userName, "");
        delete user;
        user = NULL;
        log_ui->waring4->setText(s2q("Wrong password"));
        return false;
    }
}

void login::on_logid_textEdited(const QString &arg1)
{
        log_ui->label_name->setVisible(false);
}

void login::on_logkey_textEdited(const QString &arg1)
{
    log_ui->label_2->setVisible(false);
}

void login::on_logid_editingFinished()
{
    QString userName = log_ui->logid->text();
    QString password = log_ui->logkey->text();
    getVerify(userName,password);
    Login(userName,password);
}

void login::on_logkey_editingFinished()
{
    QString userName = log_ui->logid->text();
    QString password = log_ui->logkey->text();
    getVerify(userName,password);
    Login(userName,password);
}
