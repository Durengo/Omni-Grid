//
// Created by LastWeek on 11/11/2023.
//

#include "Singleton.h"

namespace GENERICS{
    std::mutex Singleton::i_mutex;

    Singleton::Singleton() = default;

    Singleton::~Singleton() = default;
}

