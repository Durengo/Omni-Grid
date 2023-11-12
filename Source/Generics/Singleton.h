//
// Created by LastWeek on 11/11/2023.
//
#pragma once

#include <mutex>
#include "IGameLogic.h"

namespace GENERICS {
    class Singleton {
    protected:
        static std::mutex i_mutex;

    protected:
        Singleton();
        ~Singleton();
    public:
        // We don't want to allow copying of our singletons, so delete these operators
        Singleton(Singleton &other) = delete;
        void operator=(const Singleton &) = delete;
    };
}


