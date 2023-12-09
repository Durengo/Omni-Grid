#pragma once

#include <Tools/Database/database.h>

#include "User/User.h"

/**
 * @file UserMenu.h
 * @brief Contains the UserMenu class
 * @date 2023-12-06
 */

namespace Sandbox
{

    class UserMenu
    {
    private:
        SQLWRAP::Database *m_Database;
        OGRID::User *m_User;

    public:
        UserMenu();
        ~UserMenu();

        void Start();
        void FirstRun();
        void PreLoginMenu();
        void Login();
        void Register();
        void PostLoginMenu();
        // void Play();
    };

}