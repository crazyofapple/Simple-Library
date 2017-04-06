#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <string>
#include <string.h>
#include "data.h"
#include "regist.h"
#include "admin.h"
#include "user.h"
namespace Ui {
class login;
}


extern Datastore::User * IUser;

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    bool Login(QString Name, QString Password);
    bool getVerify(QString Name, QString Password);

private slots:
    void jumptoindex();
    void on_logbutton_clicked();

    void on_regbutton_clicked();

    void on_exitbutton_clicked();

    void on_logid_textEdited(const QString &arg1);

    void on_logkey_textEdited(const QString &arg1);

    void on_logid_editingFinished();

    void on_logkey_editingFinished();

signals:
    void send(QString);
    void send2(QString);
    void closing();
private:
    Ui::login *log_ui;
    regist* reg;
    admin *Admin;
    user *User;
};

#endif // LOGIN_H
