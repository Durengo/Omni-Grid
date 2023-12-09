#include "User.h"

namespace OGRID
{
    // Constructors & Destructors

    User::User(std::string userName, std::string userPassword, std::string userFirstName = "", std::string userLastName = "")
    {
    }

    User::~User()
    {
    }

    // Getters & Setters
    std::string User::GetUserName() const
    {
        return m_UserName;
    }

    void User::SetUserName(const std::string &userName)
    {
        m_UserName = userName;
    }

    std::string User::GetUserPassword() const
    {
        return m_UserPassword;
    }

    void User::SetUserPassword(const std::string &userPassword)
    {
        m_UserPassword = userPassword;
    }

    std::string User::GetUserFirstName() const
    {
        return m_UserFirstName;
    }

    void User::SetUserFirstName(const std::string &userFirstName)
    {
        m_UserFirstName = userFirstName;
    }

    std::string User::GetUserLastName() const
    {
        return m_UserLastName;
    }

    void User::SetUserLastName(const std::string &userLastName)
    {
        m_UserLastName = userLastName;
    }
}