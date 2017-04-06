#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "config.h"
using namespace std;
#include "myuser.h"
#include "data.h"
//维护
namespace UserManager
{
    //创建新用户
    bool InsertUser(string Name, string Password)
    {
        auto TemporaryUser = Datastore::Select<Datastore::User>([Name](const Datastore::User* user){
            return user->userName==Name;
        });
        if (TemporaryUser != NULL)
        {
            delete TemporaryUser;
            TemporaryUser = NULL;
            return false;
        }
        else
        {
            auto user = Datastore::Create<Datastore::User>();
            char name[LEN_USER_NAME];
            char password[LEN_USER_PASSWORD];
            char type[LEN_USER_TYPE] = "user";
            char info[LEN_USER_INFO];
            memset(name, 0, sizeof(name));
            memset(password, 0, sizeof(password));
            memset(info, 0, sizeof(info));
            for (int i = 0; Name[i] != 0; i++){ name[i] = Name[i]; }
            for (int i = 0; Password[i] != 0; i++){ password[i] = Password[i]; }
            strcpy(user->userName, name);
            strcpy(user->password, password);
            strcpy(user->info, info);
            strcpy(user->type, type);
            user->borrowMax = Config::MAX_BOLLOW_TIME;
            user->isDeleted = false;
            Datastore::InsertOrUpdate(user);
            delete user;
            user = NULL;
            delete TemporaryUser;
            TemporaryUser = NULL;
            TemporaryUser = Datastore::Select<Datastore::User>([Name](const Datastore::User* user){
                return user->userName == Name;
            });
            if (TemporaryUser != NULL)
            {
                delete TemporaryUser;
                TemporaryUser = NULL;
                return true;
            }
            else
            {
                delete TemporaryUser;
                TemporaryUser = NULL;
                return false;
            }
        }
    }
    //选择用户
    Datastore::User * SelectUser(string Name)
    {
        auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return user->userName == Name;
        });
        return user;
    }
    //删除用户
    bool DeleteUser(string Name)
    {
        auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return user->userName == Name;
        });
        if (user == NULL)return false;
        // 不能删除管理员自己
        if (!strcmp(user->type, "admin")) return false;
        Datastore::Delete<Datastore::User>(user->ID);
        delete user;
        user = NULL;
        user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return user->userName == Name;
        });
        if (user == NULL)
        {
            delete user;
            user = NULL;
            return true;
        }
        else
        {
            delete user;
            user = NULL;
            return false;
        }
    }
    //更新用户密码
    bool UpdataUserPassword(string Name, string Password)
    {

        auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return !strcmp(user->userName, Name.c_str());
        });
        if (user == NULL)return false;
        memset(user->password, 0, sizeof(user->password));
        strcpy(user->password, q2s(encrypt(s2q(Password))).c_str());
        Datastore::InsertOrUpdate(user);
        delete user;
        user = NULL;

        user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return !strcmp(user->userName, Name.c_str());
        });
        if (!strcmp(user->password, q2s(encrypt(s2q(Password))).c_str()))
        {
            delete user;
            user = NULL;
            return true;
        }
        else
        {
            delete user;
            user = NULL;
            return false;
        }
    }
    //更新用户INFO
    bool UpdataUserInfo(string Name, string Info)
    {

        auto user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return user->userName == Name;
        });
        if (user == NULL)return false;
        memset(user->info, 0, sizeof(user->info));
        strcpy(user->info, &Info[0]);
        Datastore::InsertOrUpdate(user);
        delete user;
        user = NULL;

        user = Datastore::Select<Datastore::User>([Name](const Datastore::User* user) {
            return user->userName == Name;
        });
        if (user->info == Info)
        {
            delete user;
            user = NULL;
            return true;
        }
        else
        {
            delete user;
            user = NULL;
            return false;
        }
    }
}
