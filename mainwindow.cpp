#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <string>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(settext()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::settext()
{
    Datastore::Init(false);
    auto user = Datastore::Create<Datastore::User> ();
    char name[LEN_USER_NAME] = "abd";
    char password[LEN_USER_PASSWORD] = "123";
    char type[LEN_USER_TYPE] = "user";
    char info[LEN_USER_INFO] = "123";

    strcpy_s(user->userName, name);
    strcpy_s(user->password, password);
    strcpy_s(user->info, info);
    strcpy_s(user->type, type);
    user->borrowMax = 12;
    user->isDeleted = false;

    Datastore::InsertOrUpdate(user);
    delete user;
    char Name[LEN_USER_NAME] = "abd";
    auto user2 = Datastore::Select<Datastore::User>([&](const Datastore::User* user3) {
        return !strcmp(Name, user3->userName);
    });
    QString test = "hello";
    if (!user2) ui->label->setText(test);
    else {
        ui->label->setText(QString(QString::fromLocal8Bit(user2->userName)));
        ui->label_2->setText(QString(QString::fromLocal8Bit(user2->password)));
        ui->label_3->setText(QString(QString::fromLocal8Bit(user2->type)));
        ui->label_4->setText(QString(QString::fromLocal8Bit(user2->info)));
        ui->label_5->setText(QString::number(user2->ID));
    }
}
