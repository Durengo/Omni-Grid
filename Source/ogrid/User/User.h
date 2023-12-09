#pragma once

#include <string>

/**
 * @file User.h
 * @brief Contains the User class
 * @date 2023-12-06
 * @todo Implement sqlite database into the user
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

        // Constructors & Destructors
    public:
        User(std::string userName, std::string userPassword, std::string userFirstName = "", std::string userLastName = "");
        ~User();

        // Getters & Setters
    public:
        std::string GetUserName() const;
        void SetUserName(const std::string &userName);

        std::string GetUserPassword() const;
        void SetUserPassword(const std::string &userPassword);

        std::string GetUserFirstName() const;
        void SetUserFirstName(const std::string &userFirstName);

        std::string GetUserLastName() const;
        void SetUserLastName(const std::string &userLastName);
    };
}