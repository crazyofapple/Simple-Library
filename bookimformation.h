#ifndef BOOKIMFORMATION_H
#define BOOKIMFORMATION_H

#include <QDialog>
#include "data.h"
namespace Ui {
class bookImformation;
}

class bookImformation : public QDialog
{
    Q_OBJECT
    
public:
    explicit bookImformation(QWidget *parent = 0);
    ~bookImformation();
    void tableshow();
    void table2show();
    void showRecord(Datastore::Book *);
    void showRecord2(Datastore::Book *, int i);
private slots:
    void receive(QString, QString, QString, QString);
private:
    Ui::bookImformation *ui;
    QString bookName, ISBN, bookAuthor, bookPublisher;
};

#endif // BOOKIMFORMATION_H
