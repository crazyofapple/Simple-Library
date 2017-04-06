#ifndef INDEX_H
#define INDEX_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include "data.h"
#include "booker.h"
#include "login.h"
#include "bookimformation.h"
namespace Ui {
class index;
}

class index : public QDialog
{
    Q_OBJECT
    
public:
    int getRadioButton();
    void printBookList(Datastore::Book** list);
    void clear();
    explicit index(QWidget *parent = 0);
    ~index();
    
private slots:
    void on_button_search_clicked();

    void on_button_tologin_clicked();

    void on_page_next_clicked();

    void on_page_prev_clicked();

    void on_button_exit_clicked();
    void on__15_clicked();

    void on__25_clicked();

    void on__35_clicked();

    void on__45_clicked();

    void showagain();
signals:
    void send(QString bookname, QString ISBN, QString author, QString publisher);
private:
    Ui::index *ui;
    vector<Datastore::Book *> vt;
    vector<pair<Datastore::Book *, int> > newVt;
    int nowCnt;
    int prevRecordNum, nowRecordNum;
    login* log;
    bookImformation * bookinformation;
};

#endif // INDEX_H
