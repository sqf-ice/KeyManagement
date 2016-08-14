//
// Copyright (c) 2016 航天二院爱威公司. All rights reserved.
//
// Author Hanzeil.
//

#ifndef KEYMANAGEMENT_MYSQLFACTORY_H
#define KEYMANAGEMENT_MYSQLFACTORY_H

#include "../DBFactoryInterface.h"

class MysqlFactory : public DBFactoryInterface {
public:
    explicit MysqlFactory() = default;

    ~MysqlFactory();

    DBProductInterface *createProduct();
};


#endif //KEYMANAGEMENT_MYSQLFACTORY_H
