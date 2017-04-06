#ifndef REGIST_H
#define REGIST_H

#include <QDialog>

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT
    
public:
    explicit regist(QWidget *parent = 0);
    ~regist();
    bool InsertUser(QString Name, QString Password, QString info = "");
private slots:
    void on_regb_clicked();

    void on_exit2Login_clicked();
    void on_logid_editingFinished();

    void on_logkey_editingFinished();

    void on_logkeysure_editingFinished();

private:
    Ui::regist *reg_ui;
};

#endif // REGIST_H
