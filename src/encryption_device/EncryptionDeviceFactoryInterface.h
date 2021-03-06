//
// Created by Hanzeil on 16-8-15.
//
// Copyright (c) 2016 航天二院爱威公司. All rights reserved.
//
// Author Hanzeil.
//
// 加密硬件工厂接口，可以生产多种加密硬件接口，目前支持SJK1238, Simulation
//

#ifndef KEYMANAGEMENT_ENCRYPTION_DEVICE_FACTORY_INTERFACE_H
#define KEYMANAGEMENT_ENCRYPTION_DEVICE_FACTORY_INTERFACE_H

#include <memory>
#include "EncryptionDeviceProductInterface.h"

namespace encryption_device {

    class EncrpytionDeviceFactoryInterface {
    public:
        EncrpytionDeviceFactoryInterface() = default;

        virtual ~EncrpytionDeviceFactoryInterface();

        virtual std::shared_ptr<EncryptionDeviceProductInterface> CreateProduct()=0;
    };

}

#endif //KEYMANAGEMENT_ENCRYPTION_DEVICE_FACTORY_INTERFACE_H
