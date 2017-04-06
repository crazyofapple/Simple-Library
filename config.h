#ifndef CONFIG_H
#define CONFIG_H

namespace Config {

    //数据实体属性长度，注意 extern const 不能作为数组长度
    #define LEN_BOOK_ISBN 14
    #define LEN_BOOK_NAME 100
    #define LEN_BOOK_AUTHOR 100
    #define LEN_BOOK_PUBLISHER 100
    #define LEN_USER_NAME 100
    #define LEN_USER_PASSWORD 40
    #define LEN_USER_TYPE 10
    #define LEN_USER_INFO 100

    //借阅期限
    extern const int MAX_BOLLOW_TIME;

    //数据存储文件所在的目录
    extern const char* DATASTORE_PATH;

    //数据存储文件读取缓存，每次读取的记录条数
    extern const int FILE_READ_CACHE_COUNT;

}

#endif // CONFIG_H
