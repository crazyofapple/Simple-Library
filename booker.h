#ifndef BOOKER_H
#define BOOKER_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "data.h"

using namespace std;

namespace Booker{
///内部使用
    extern string Temp, AnotherTemp;
    extern int BookID, UserID;
    //Isbn搜索图书
    bool SearchBookCondition(const Datastore::Book* book);
    //User查找条件
    bool SearchUserCondition(const Datastore::User* user);
    //bookID&userID搜索记录
    bool SearchRecordCondition(const Datastore::Record* record);

///外部InterFace
    //增加图书
    int AddBook(string Isbn, string Name, string Author, string Publisher, double price);

    //删除图书
    bool DeleteBook(int ID);

    //Isbn查找图书
    Datastore::Book** IsbnFindBook(string Isbn);

    //ID查找图书
    Datastore::Book* IDFindBook(int ID);

    //Anything查找图书
    Datastore::Book** AnythingFindBook(string Anything);

    //借书
    bool BrowseBook(string userName, int ID);

    //1正常还书,0超期还书,-1还书失败
    int ReturnBook(string userName, int ID);

    //续借
    //超时不能续借，用户名或书ISBN错误不能续借，已续借不能续借，已还不能续借
    bool RenewBook(string Account, string Isbn);

    Datastore::Record** userIDFindRecord(int userID);
    Datastore::Record* recordIDFindRecord(int recordID);
}
#endif // BOOKER_H
