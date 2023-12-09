#pragma once

#include <Tools/Database/database.h>

#include "User/User.h"

/**
 * @file UserMenu.h
 * @brief Contains the UserMenu class
 * @date 2023-12-09
 */

namespace Sandbox
{
    /**
     * @brief The UserMenu class
     * @details This class is used to manage the user menu and interact with the database
     * @date 2023-12-09
     * @see User
     * @see Database
     */
    class UserMenu
    {
    private:
        /**
         * @brief The Database object
         * @date 2023-12-09
         */
        SQLWRAP::Database *m_Database;

        /**
         * @brief The User object
         * @date 2023-12-09
         */
        OGRID::User *m_User;

    public:
        /**
         * @brief Construct a new UserMenu object
         * @date 2023-12-09
         */
        UserMenu();

        /**
         * @brief Destroy the UserMenu object
         * @date 2023-12-09
         */
        ~UserMenu();

        /**
         * @brief Starts the user menu
         * @date 2023-12-09
         */
        void Start();

    private:
        /**
         * @brief Creates the database tables if they don't exist
         * @date 2023-12-09
         */
        void FirstRun();

        /**
         * @brief Displays the pre-login menu
         * @date 2023-12-09
         */
        void PreLoginMenu();

        /**
         * @brief Displays the post-login menu
         * @date 2023-12-09
         */
        void Login();

        /**
         * @brief Displays the register menu
         * @date 2023-12-09
         */
        void Register();

        /**
         * @brief Displays the post-login menu
         * @date 2023-12-09
         */
        void PostLoginMenu();
    };
}