#include "booker.h"

#include "booker.h"

namespace Booker{
    ///内部使用
    //Isbn查找条件
    string Temp, AnotherTemp;
    int BookID, UserID;
    //book查找条件
    bool SearchBookCondition(const Datastore::Book* book)
    {
        return !strcmp(book->ISBN, &Temp[0]);
    }
    //User查找条件
    bool SearchUserCondition(const Datastore::User* user)
    {
        return !strcmp(user->userName, &Temp[0]);
    }
    // 其它查找条件
    bool SearchAsSomething(const Datastore::Book* book)
    {
        return book->ISBN == Temp ||
            strstr(book->bookName, Temp.data()) ||
            strstr(book->bookAuthor, Temp.data()) ||
            strstr(book->bookPublish, Temp.data());
    }
    // 记录查找条件
    bool SearchRecordCondition(const Datastore::Record* record) {
        return (record->userId == UserID) && (record->bookId == BookID);
    }
    bool SearchRecordCondition2(const Datastore::Record* record) {
        return (record->userId == UserID);
    }
    Datastore::Record** IDFindRecord(int userID, int bookID) {
        UserID = userID;
        BookID = bookID;
        Datastore::Record **record = Datastore::Selects<Datastore::Record>(SearchRecordCondition);
        return record;
    }
    Datastore::Record** userIDFindRecord(int userID) {
        UserID = userID;
        Datastore::Record **record = Datastore::Selects<Datastore::Record>(SearchRecordCondition2);
        return record;
    }

    Datastore::Record* recordIDFindRecord(int recordID)
    {
        auto record = Datastore::Select<Datastore::Record>([recordID](const Datastore::Record* record)
        {
            return record->ID == recordID;
        });
        return record;
    }

    ///外部InterFace
    //增加图书
    int AddBook(string Isbn, string Name, string Author, string Publisher, double price)
    {
        Datastore::Book *books = Datastore::Create<Datastore::Book>();
        strcpy(books->bookName, &Name[0]);
        strcpy(books->ISBN, &Isbn[0]);
        strcpy(books->bookAuthor, &Author[0]);
        strcpy(books->bookPublish, &Publisher[0]);
        books->canBorrow = true;
        books->price = price;
        books->isDeleted = false;
        int ID = Datastore::InsertOrUpdate(books);
        return ID;
    }



    //Isbn查找Book
    Datastore::Book** IsbnFindBook(string Isbn)
    {
        Temp = Isbn;

        Datastore::Book **book = Datastore::Selects<Datastore::Book>(SearchBookCondition);

        return book;
    }

    //搜索条件查找图书
    Datastore::Book** AnythingFindBook(string Anything)
    {
        Temp = Anything;

        Datastore::Book **book = Datastore::Selects<Datastore::Book>(SearchAsSomething);

        return book;
    }

    //借阅图书
    bool BrowseBook(string userName, int ID)
    {
        Temp = userName;
        Datastore::User **user = Datastore::Selects<Datastore::User>(SearchUserCondition);
        Datastore::Book *book = IDFindBook(ID);

        if (user[0] != NULL && book != NULL)
        {
            book->canBorrow = false;
            Datastore::InsertOrUpdate(book);

            Datastore::Record *record = new Datastore::Record;
            record->userId = user[0]->ID;
            record->bookId = book->ID;
            record->borrowTime = time(0);
            record->returnTime = time(0);
            // 在借阅时 borrowTime = returnTime
            record->isBorrowed = true;
            record->isRenew = false;
            record->isDeleted = false;
            record->ID = -1;
            Datastore::InsertOrUpdate(record);
            delete[] user;
            book = NULL;
            user = NULL;
            return true;
        }

        return false;
    }

    //归还图书
    //1正常还书,0超期还书,-1还书失败
    int ReturnBook(string userName, int ID)
    {
        Temp = userName;
        Datastore::User **user = Datastore::Selects<Datastore::User>(SearchUserCondition);

        Datastore::Book *book = IDFindBook(ID);
        if (user[0] == NULL || book == NULL)return -1;

        Datastore::Record **record = IDFindRecord(user[0]->ID, book->ID);

        delete[] user;
        user = nullptr;
        for (int i = 0; record[i] != NULL; i++)
        {
            if (record[i]->isBorrowed == true && record[i]->borrowTime == record[i]->returnTime)
            {
                record[i]->isBorrowed = false;
                record[i]->returnTime = time(0);
                book->canBorrow = true;
                Datastore::InsertOrUpdate(book);
                book = nullptr;
                Datastore::InsertOrUpdate(record[i]);
                int Time = time(0) - record[i]->borrowTime;
                int Day = Time / 86400;
                int BD = Config::MAX_BOLLOW_TIME;//借书期限
                if (record[i]->isRenew == true)BD = 2 * Config::MAX_BOLLOW_TIME;
                if (Day > BD)
                {
                    return 0;
                }
                else{
                    return (BD - Day);
                }
            }
        }

        return -1;
    }
    //删除图书
    bool DeleteBook(int ID)
    {
        auto book = Datastore::Select<Datastore::Book>([ID](const Datastore::Book* book) {
            return book->ID == ID;
        });
        if (book == nullptr) {
            return false;
        }else {
            Datastore::Delete<Datastore::Book>(book->ID);
            return true;
        }
    }
    // 续借图书
    bool RenewBook(string Account, string Isbn)
    {
        return true;
    }

    //ID查找图书
    Datastore::Book* IDFindBook(int ID)
    {
        auto book = Datastore::Select<Datastore::Book>([ID](const Datastore::Book* book) {
            return book->ID == ID;
        });
        return book;
    }
}
