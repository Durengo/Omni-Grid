#include "User.h"

#include "Score.h"

namespace OGRID
{
    // Constructors & Destructors

    User::User()
        : m_UserName(""), m_UserPassword(""), m_UserFirstName(""), m_UserLastName(""), m_Score(nullptr)
    {
    }

    User::User(std::string userName, std::string userPassword, std::string userFirstName = "", std::string userLastName = "", Score *score)
        : m_UserName(userName), m_UserPassword(userPassword), m_UserFirstName(userFirstName), m_UserLastName(userLastName), m_Score(score)
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