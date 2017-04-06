#ifndef DATA_H
#define DATA_H
#pragma execution_character_set("utf-8")
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <functional>
#include <string>
#include <list>
#include <direct.h>
#include <QString>
#include "config.h"
#include <string>
#include <iostream>
using namespace std;

namespace Datastore {

    // 图书信息
    struct Book
    {
        int  ID;
        char bookName[LEN_BOOK_NAME];
        char bookAuthor[LEN_BOOK_AUTHOR];
        char bookPublish[LEN_BOOK_PUBLISHER];
        char ISBN[LEN_BOOK_ISBN];
        bool canBorrow;
        double price;
        bool isDeleted;
    };

    // 用户
    struct User
    {
        int ID;
        char userName[LEN_USER_NAME];
        char password[LEN_USER_PASSWORD];
        char type[LEN_USER_TYPE];
        unsigned int borrowMax;
        char info[LEN_USER_INFO];
        bool isDeleted;

    };

    // 借阅记录
    struct Record
    {
        int ID;
        time_t borrowTime;
        time_t returnTime; //没还为空
        int userId;
        int bookId;
        bool isBorrowed;
        bool isRenew;
        bool isDeleted;
    };


    // 检测存储某种类型的文件是否存在
    char* _GenerateFilePathByTypeName(const char* name);
    template <typename T>
    bool _IsFileExist() {
        auto file = fopen(_GenerateFilePathByType<T>(), "rb");
        auto exist = true;
        if (file == NULL) {
            exist = false;
        } else {
            fclose(file);
        }
        return exist;
    }
    template <typename T>
    char* _GenerateFilePathByType() {
        auto name = typeid(T).name();
        return _GenerateFilePathByTypeName(name);
    }
    // 创建某个记录
    template <typename T>
    T* Create() {
        auto item = new T();
        memset(item, 0, sizeof T);
        item->ID = -1;
        return item;
    }



    // 打开存储某种类型的文件
    template <typename T>
    FILE* _OpenFile() {
        FILE *file = fopen(_GenerateFilePathByType<T>(), "rb+");
        if (file == NULL) {
            throw new std::exception("文件打开失败");
        }
        //允许程序控制缓冲和stream 的缓冲区大小
        setvbuf(file, NULL, _IOFBF, (sizeof T) * Config::FILE_READ_CACHE_COUNT);
        return file;
    }

    // 根据 ID 选择某个记录
    template <typename T>
    T* Select(int ID) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        auto item = new T();
        fseek(file, size * ID, SEEK_SET);
        fread(item, size, 1, file);
        return item;
    }

    // 根据条件选择一些记录
    // 返回 NULL 结尾的数组
    // where: 搜索条件
    template <typename T>
    T** Selects(const std::function<bool(const T*)> where, int beginID = 0, int maxCount = -1) {
        auto temp = std::list<T*>();
        auto count = 0;
        Traverse<T>([&](const T* item) {
            if (where(item)) {
                T* t = new T();
                memcpy(t, item, sizeof T);
                temp.push_back(t);
                count++;
            }
            return count != maxCount;
        }, beginID);

        auto result = new T*[temp.size() + 1];
        int i = 0;
        for (auto it=temp.begin(); it != temp.end(); it++) {
            result[i] = *it;
            i++;
        }
        result[temp.size()] = NULL;
        return result;
    }

    // 根据条件选择一个记录
    // 返回符合条件的第一个记录，没有找到时返回 NULL
    // where: 搜索条件
    template <typename T>
    T* Select(const std::function<bool(const T*)> where, int beginID = 0) {
        auto results = Selects(where, beginID, 1);
        auto result = *results;
        delete [] results;
        return result;
    }

    // 插入或更新一个记录
    template <typename T>
    int InsertOrUpdate(T* item) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        if (item->ID == -1) {
            fseek(file, 0, SEEK_END);
            auto offset = ftell(file);
            item->ID = offset / size;
        } else {
            fseek(file, size * item->ID, SEEK_SET);
        }
        fwrite(item, size, 1, file);
        fclose(file);
        return item->ID;
    }

    // 删除一个记录
    template <typename T>
    void Delete(int ID) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        T* item = new T();
        fseek(file, size * ID, SEEK_SET);
        fread(item, size, 1, file);
        item->isDeleted = true;
        fseek(file, size * ID, SEEK_SET);
        fwrite(item, size, 1, file);
        delete item;
        fclose(file);
    }

    // 遍历一种记录
    // func: 操作一个记录的函数
    template <typename T>
    void Traverse(const std::function<bool(const T*)> func, int beginID = 0, int endID = 0) {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        T* item = new T();

        fseek(file, 0, SEEK_END);
        auto count = ftell(file) / size;

        if (endID <= 0) {
            endID += count;
        }

        fseek(file, beginID * size, SEEK_SET);
        for (auto i = beginID; i < endID; i++) {
            fread(item, size, 1, file);
            if (!item->isDeleted && !func(item)) {
                break;
            }
        }

        delete item;
    }
    template <typename T>
    void clear() {
        auto file = _OpenFile<T>();
        auto size = sizeof T;
        T* item = new T();
        fseek(file, 0, SEEK_END);
        auto count = ftell(file) / size;
        for (int i = 0; i < count; i++) {

        }
    }

    // 数据存储初始化，创建相关目录和文件并添加初始信息
    // force: 为 true 时忽略现有文件强制初始化
    void Init(bool force = false);
}
// string转化为QString
QString s2q(const string &s);
// QString转化为string
string q2s(const QString &s);
// 判断用户名是否合法
bool isEmailAddress(QString strEmailAddr);
// 判断密码是否合法
bool isLegalPassword(QString password);
// 判断用户信息是否合法
bool isLegalInfo(QString info);
// 把密码转化为其hash值
QString encrypt(QString s);
// 判断ISBN号是否合法
bool isbnCheck(string str);
bool allNumric(const char * str);
// 判断string是否是vaild number
bool isNumber(const char *s);
//去除字符串前后的空格
string &_ltrim(string &s);
string &_rtrim(string &s);
string &_trim(string &s);
#endif // DATA_H
