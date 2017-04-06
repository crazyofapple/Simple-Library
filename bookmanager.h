#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QDialog>
namespace Ui {
class bookManager;
}

class bookManager : public QDialog
{
    Q_OBJECT
    
public:
    explicit bookManager(QWidget *parent = 0);
    ~bookManager();
    void bookManager::clear();
    void refresh(int flag);
    
private slots:

    void on_pushButton_addBook_clicked();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_6_editingFinished();


    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_14_clicked();

    void on_low_2_textChanged(const QString &arg1);


    void on_low_3_clicked();

    void on_pushButton_15_clicked();

    void on_low_5_clicked();

    void on_pushButton_16_clicked();
    void myshow();
private:
    int ID;
    Ui::bookManager *ui;
    int flag; // 1 borrow, 2 return
};

#endif // BOOKMANAGER_H
