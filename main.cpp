#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include "login.h"
#include "data.h"
#include "index.h"
#include "bookmanager.h"
#include "bookmanager.h"
#include "usermanager.h"
#include "admin.h"
#include "bookimformation.h"
#include <qmessagebox.h>
int __main ()
{
    /*if (Datastore::_IsFileExist<Datastore::Book>() &&
            Datastore::_IsFileExist<Datastore::User>() &&
              Datastore::_IsFileExist<Datastore::Record>()){
        return 1;
    }*/
    Datastore::Init(true);
    ifstream infile("c://in.txt");
    string temp;
    while (getline(infile, temp))
    {
        auto TmpBook = Datastore::Create<Datastore::Book>();
        strcpy(TmpBook->bookName, temp.c_str());
        getline(infile, temp);
        strcpy(TmpBook->bookAuthor, temp.c_str());
        getline(infile, temp);
        strcpy(TmpBook->bookPublish, temp.c_str());
        getline(infile, temp);
        strcpy(TmpBook->ISBN, temp.c_str());
        TmpBook->canBorrow = true;
        TmpBook->price = 100.0;
        TmpBook->isDeleted = false;
        Datastore::InsertOrUpdate(TmpBook);
        delete TmpBook;
        //QMessageBox::warning(NULL,"Success","hehe",QMessageBox::Yes);
    }

    return 0;
}
int main(int argc, char *argv[])
{
    int x = __main();
    qDebug("%d",x);
    QApplication a(argc, argv);
    index indexpage;
    indexpage.show();
    return a.exec();
}
