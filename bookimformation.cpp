#include "bookimformation.h"
#include "ui_bookimformation.h"
#include "booker.h"
#include <algorithm>
#include <string>
#include <sstream>
bookImformation::bookImformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookImformation)
{
    ui->setupUi(this);
    ui->table->setSelectionBehavior ( QAbstractItemView::SelectRows);//璁剧疆閫夋嫨琛屼负锛屼互琛屼负鍗曚綅
    ui->table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
    ui->table->clearContents();

}

bookImformation::~bookImformation()
{
    delete ui;
}

void bookImformation::receive(QString _bookName, QString _ISBN, QString _bookAuthor, QString _bookPublisher){
    bookName = _bookName;
    ISBN = _ISBN;
    bookAuthor = _bookAuthor;
    bookPublisher = _bookPublisher;
    ui->label_100->setText(_bookName);ui->label_100->adjustSize();
    ui->label_200->setText(_ISBN);ui->label_200->adjustSize();
    ui->label_300->setText(_bookAuthor);ui->label_300->adjustSize();
    ui->label_400->setText(_bookPublisher);ui->label_400->adjustSize();
    tableshow();
    table2show();
}


void bookImformation::showRecord(Datastore::Book* aBook){
    int aBookId = aBook->ID;
    Datastore::Record** record = Datastore::Selects<Datastore::Record>(
                [&](const Datastore::Record* record){
        return (record->bookId == aBookId);
    });
    if (!record[0]) return;
    int i = 0;
    qDebug("ok hadaha2 %d", record[i]->ID);
    while(record[i] != nullptr){
        qDebug("ok hadaha3");
        ui->table->insertRow( ui->table->rowCount() );
        ui->table->setItem(ui->table->rowCount() - 1, 0, new QTableWidgetItem(s2q(std::to_string(aBookId))));
        ui->table->setItem(ui->table->rowCount() - 1, 1, new QTableWidgetItem(s2q(ctime(&record[i]->borrowTime))));

        if (record[i]->borrowTime != record[i]->returnTime){
            ui->table->setItem(ui->table->rowCount() - 1, 2, new QTableWidgetItem(s2q(ctime(&record[i]->returnTime))));
        }
        if (record[i]->isBorrowed) {
            ui->table->setItem(ui->table->rowCount() - 1, 3, new QTableWidgetItem("borrow"));
        }else if (record[i]->isRenew) {
            ui->table->setItem(ui->table->rowCount()-1, 3, new QTableWidgetItem("borrow"));
        }else {
            ui->table->setItem(ui->table->rowCount()-1, 3, new QTableWidgetItem("return"));
        }
        i++;
    }

}
void bookImformation::showRecord2(Datastore::Book * aBook, int i) {
    ui->table_2->insertRow( ui->table_2->rowCount() );
    char buff[100];
    sprintf(buff, "%010d", aBook->ID);
    string str = buff;
    
    qDebug("%s",str.c_str());
    ui->table_2->setItem(ui->table_2->rowCount() - 1, 0, new QTableWidgetItem(s2q(str)));
    string state;
    if (i == 0) state = "馆藏本";
    else if (aBook->canBorrow) state = "在馆";
    else state = "在借";
    ui->table_2->setItem(ui->table_2->rowCount() - 1, 1, new QTableWidgetItem(s2q(state)));
    ui->table_2->setItem(ui->table_2->rowCount() - 1, 2, new QTableWidgetItem(s2q("崂山校区图书馆二楼")));

}

void bookImformation::table2show() {
    while (ui->table_2->rowCount() > 0) {
        ui->table_2->removeRow(0);
    }
    Datastore::Book**  bookList  = Booker::IsbnFindBook(q2s(ISBN));
    if (bookList == nullptr ) return;
    int i = 0;
    //qDebug("ok hadaha");
    while(bookList[i] != nullptr) {
        showRecord2(bookList[i],i);
        i++;
    }
}

void bookImformation::tableshow() {
    while (ui->table->rowCount() > 0)
    {
        ui->table->removeRow(0);
    }
    Datastore::Book**  bookList  = Booker::IsbnFindBook(q2s(ISBN));
    if (bookList == nullptr ) return;
    int i = 0;
    //qDebug("ok hadaha");
    while(bookList[i] != nullptr) {
        showRecord(bookList[i]);
        i++;
    }
}
