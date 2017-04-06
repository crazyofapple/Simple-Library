#include <QCryptographicHash>
#include "config.h"
#include "data.h"
#include <QRegExp>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}

bool isEmailAddress(QString strEmailAddr)
{
    if ( strEmailAddr.length() == 0 ) return false;
    QString strPatt = "\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b";
    QRegExp rx(strPatt);
    return rx.exactMatch(strEmailAddr);
}
bool isLegalPassword(QString password){
    char code[16] = {'@', '#', '$', '%', '^', '&', '*', '+', '/', '=', '!', '?', '-', '_', '(', ')'};
    if (password.length() < 4 || password.length() > 10) {
        return false;
    }
    for (int i = 0; i < password.length(); i++) {
        auto a = password[i];
        if (a >= '0' && a <= '9'){
            continue;
        }
        if (a >= 'A' && a <= 'Z'){
            continue;
        }
        if (a >= 'a' && a <= 'z'){
            continue;
        }
        int j;
        for (j = 0; j < 16; j++){
            if (a == code[i]){
                break;
            }
        }
        if (j != 17) continue;
        return false;
    }
    return true;
}
//将口令变为其hash值
QString encrypt(QString s){
    char name[LEN_USER_PASSWORD];
    strcpy(name, s.toStdString().c_str());
    QString blah = QString(QCryptographicHash::hash((name),QCryptographicHash::Md5).toHex());
    return blah;
}
//验证字符串每一位都是数字且没有先导0的长串或只有一个0
bool allNumric(const char * str){
    if('0' == str[0]){
        if('\0' == str[1]){
            return true;
        }
        return false;
    }
    int i = 0;
    while(str[i]!='\0'){
        if(str[i] < '0' || str[i] >'9'){
            return false;
        }
        i++;
    }
    return true;
}
//ISBN合法性检测(仅检测长度以及是否由纯数字和末尾可能的X/x组成)
bool isbnCheck(string str){
    if((str.size() != 13 && str.size() != 10)){
        return false;
    }
    if(13 == str.size()){
        if(allNumric(str.c_str())){
            return true;
        }
    }else if(allNumric(str.c_str()) || (allNumric(str.substr(0,str.size() - 2).c_str()) &&
                                        ('X' == str.at(str.size() - 1) ||  'x' == str.at(str.size() - 1)))){
        return true;
    }
    return false;
}
// 判断用户信息是否合法
bool isLegalInfo(QString info) {
    return info.length() >= 0 && info.length() < 20;
}
int my_isspace( int ch )
{
    return (unsigned int)(ch - 9) < 5u  ||  ch == ' ';
}
// trim from start
string &_ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(my_isspace))));
        return s;
}

// trim from end
string &_rtrim(string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(my_isspace))).base(), s.end());
        return s;
}

// trim from both ends
string &_trim(string &s) {
        return _ltrim(_rtrim(s));
}
// Validate if a given string is numeric.
bool isNumber(const char *s) {
        char *ptr = nullptr;
        strtod(s, &ptr);
        if (ptr == s) return false;
        while (*ptr!='\0'){
            if (*ptr!=' ')return false;
            ptr++;
        }
        return true;
}

namespace Datastore {

// 根据实体类型生成文件名
char* _GenerateFilePathByTypeName(const char* name) {
    auto lengthName = strlen(name);
    auto lengthPath = strlen(Config::DATASTORE_PATH);
    auto filepath = new char[lengthPath + lengthName + 5];

    strcpy(filepath, Config::DATASTORE_PATH);
    strcpy(filepath + lengthPath, name);

    for (auto i = lengthPath; i < lengthPath + lengthName; i++) {
        if (strchr("\\/:*?\"<>| ", filepath[i]) != NULL) {
            filepath[i] = '_';
        }
    }
    filepath[lengthPath + lengthName]='.';
    filepath[lengthPath + lengthName + 1]='d';
    filepath[lengthPath + lengthName + 2]='a';
    filepath[lengthPath + lengthName + 3]='t';
    filepath[lengthPath + lengthName + 4]='\0';
    return filepath;
}
void Init(bool force) {
    _mkdir(Config::DATASTORE_PATH);

    if (force || !_IsFileExist<Book>()) {
        fclose(fopen(_GenerateFilePathByType<Book>(), "wb"));
    }
    if (force || !_IsFileExist<User>()) {
        fclose(fopen(_GenerateFilePathByType<User>(), "wb"));

        User* user;

        user = Create<User>();
        strcpy(user->userName, "admin@admin.com");
        QString password = "admin";
        strcpy(user->password, encrypt(password).toStdString().c_str());
        strcpy(user->type, "admin");
        InsertOrUpdate(user);
        delete user;

        user = Create<User>();
        strcpy(user->userName, "user@admin.com");
        password = "user";
        strcpy(user->password, encrypt(password).toStdString().c_str());
        strcpy(user->type, "user");
        InsertOrUpdate(user);
        delete user;
    }
    if (force || !_IsFileExist<Record>()) {
        fclose(fopen(_GenerateFilePathByType<Record>(), "wb"));
    }
}


}
