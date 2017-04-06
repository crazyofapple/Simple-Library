#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    ui->label_01_1->setVisible(false);
    ui->label_02_2->setVisible(false);
    ui->label_03_3->setVisible(false);
    ui->lineEdit_01->setEchoMode(QLineEdit::Password);
    ui->lineEdit_02->setEchoMode(QLineEdit::Password);
    ui->lineEdit_03->setEchoMode(QLineEdit::Password);
    ui->label_11->setText("");
    ui->label_12->setText("");
    //setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);//透明
    //connect(this,SIGNAL(send()),bookmanager,SLOT(receive()));
    connect(this,SIGNAL(jumpback()),parent,SLOT(jumptoindex()));
    timerId = startTimer(30000); // 30分钟清理一次
}

admin::~admin()
{
    killTimer(timerId);
    delete ui;
}
void admin::timerEvent(QTimerEvent *event){
    qDebug("time update");
    Datastore::clear<Datastore::Book>();
    Datastore::clear<Datastore::User>();
    Datastore::clear<Datastore::Record>();
}

void admin::receive(QString str){
    userName = str;
    qDebug("hello simida");
    ui->label_11->setText(userName);
    ui->label_11->adjustSize();
    char Name[LEN_USER_NAME];
    strcpy(Name, q2s(userName).c_str());
    auto user = Datastore::Select<Datastore::User>([&](const Datastore::User* user) {
        return !strcmp(user->userName, Name);
    });
    if (user == nullptr) {
        userInfo = "";
    }else {
        userInfo = s2q((string)user->info);
    }
    ui->label_12->setText(userInfo);
}

void admin::on_lineEdit_01_textChanged(const QString &arg1)
{

    QString str = ui->lineEdit_01->text();
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
            ui->label_01_1->setVisible(false);
        }else {
            ui->label_01_1->setVisible(true);
        }
    }else {
        ui->label_01_1->setVisible(true);
    }
}
//新密码第一次输入
void admin::on_lineEdit_02_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_02->text();
    string s = _trim(q2s(str));
    if (s.size()>0&&s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))){
        ui->label_02_2->setVisible(false);
    }else {
        ui->label_02_2->setVisible(true);
    }
}
//新密码第二次输入
void admin::on_lineEdit_03_textChanged(const QString &arg1)
{
    QString str = ui->lineEdit_03->text();
    string s = _trim(q2s(str));
    if (s.size()>0 && s.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s))) {
        QString str2 = ui->lineEdit_02->text();
        string s2 = _trim(q2s(str2));
        if (s2.size()>0 && s2.size()<LEN_USER_PASSWORD&&isLegalPassword(s2q(s2)) && s2 == s) {
            ui->label_03_3->setVisible(false);
        }else {
            ui->label_03_3->setVisible(true);
        }
    }
}

void admin::on_pushButton_8_clicked()
{
    if (!ui->label_01_1->isVisible() && !ui->label_02_2->isVisible()
            && !ui->label_03_3->isVisible() && ui->lineEdit_01->text().size() > 0
                && ui->lineEdit_02->text().size() && ui->lineEdit_03->text().size() > 0) {
        if (UserManager::UpdataUserPassword(q2s(userName), _trim(q2s(ui->lineEdit_02->text())))) {
             QMessageBox::warning(this,tr("Success"),tr("change password success"),QMessageBox::Yes);
        }else {
             QMessageBox::warning(this,tr("Success"),tr("change password fail"),QMessageBox::Yes);
        }
    }else {
         QMessageBox::warning(this,tr("Success"),tr("input illegal"),QMessageBox::Yes);
    }
}

void admin::on_pushButton_clicked()
{
    qDebug("say something");
    bookManager * s = new bookManager(this);
    s->show();
    s->exec();
}

void admin::on_pushButton_2_clicked()
{
    usermanager * s = new usermanager(this);
    s->show();
    s->exec();
}

void admin::on_pushButton_test_clicked()
{
    reject();
}

void admin::on_pushButton_3_clicked()
{
    emit jumpback();
    this->close();
}

void admin::on_pushButton_4_clicked()
{
    Datastore::clear<Datastore::Book>();
    Datastore::clear<Datastore::User>();
    Datastore::clear<Datastore::Record>();
    QMessageBox::warning(this,tr("Success"),tr("clear success!!"),QMessageBox::Yes);
}
