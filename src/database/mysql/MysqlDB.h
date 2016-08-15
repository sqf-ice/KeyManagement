//
// Created by Hanzeil on 16-8-15.
//
// Copyright (c) 2016 航天二院爱威公司. All rights reserved.
//
// Author Hanzeil.
//

#ifndef KEYMANAGEMENT_MYSQL_DB_H
#define KEYMANAGEMENT_MYSQL_DB_H

#include "../DBProductInterface.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <stdexcept>
#include <boost/log/trivial.hpp>
#include <string>
#include <cstring>
#include <sstream>
#include <time.h>
#include <cstdlib>

class MysqlDB : public DBProductInterface {
public:
    explicit MysqlDB() = default;

    ~MysqlDB();

    bool Connect(std::string username, std::string password);

    bool InsertKey(Key &k);

    Key *GetKey(unsigned char *key_id);

private:
    static std::string UnixTime2MysqlTime(time_t unix_timestamp);

    static std::time_t MysqlTime2UnixTime(std::string mysql_time);

    sql::mysql::MySQL_Driver *driver_ = nullptr;
    sql::Connection *con_ = nullptr;
    std::string db_name_ = "symmetric_key";
    std::string key_table_name_ = "test";

};


#endif //KEYMANAGEMENT_MYSQL_DB_H
