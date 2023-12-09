#pragma once

#include <string>

/**
 * @file User.h
 * @brief Contains the User class
 * @date 2023-12-06
 */
namespace OGRID
{
    class User
    {
    private:
        std::string m_UserName;
        std::string m_UserPassword;
        std::string m_UserFirstName;
        std::string m_UserLastName;

    public:
        User();
        ~User();

        std::string GetUserName() const;
        std::string GetUserPassword() const;
        std::string GetUserFirstName() const;
        std::string GetUserLastName() const;

        void SetUserName(const std::string &userName);
        void SetUserPassword(const std::string &userPassword);
        void SetUserFirstName(const std::string &userFirstName);
        void SetUserLastName(const std::string &userLastName);
    };
}