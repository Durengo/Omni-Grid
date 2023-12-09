#include "User.h"

#include <durlib.h>

#include "Score.h"

namespace OGRID
{
    // Constructors & Destructors

    User::User()
        : m_UserId(0), m_UserName(""), m_UserPassword(""), m_UserFirstName(""), m_UserLastName(""), m_Score(nullptr)
    {
    }

    User::User(int userId, std::string userName, std::string userPassword, std::string userFirstName, std::string userLastName, Score *score)
        : m_UserId(userId), m_UserName(userName), m_UserPassword(userPassword), m_UserFirstName(userFirstName), m_UserLastName(userLastName), m_Score(score)
    {
    }

    User::~User()
    {
    }

    // Getters & Setters

    unsigned int User::GetUserId() const
    {
        return m_UserId;
    }

    void User::SetUserId(unsigned int userId)
    {
        m_UserId = userId;
    }

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

    Score *User::GetScore() const
    {
        return m_Score;
    }

    void User::SetScore(Score *score)
    {
        m_Score = score;
    }

    // Methods
    void User::Display() const
    {
        std::string output = "User ID: " + std::to_string(m_UserId) + "\n";
        output += "Username: " + m_UserName + "\n";
        output += "Password: " + m_UserPassword + "\n";
        output += "First Name: " + m_UserFirstName + "\n";
        output += "Last Name: " + m_UserLastName + "\n";

        if (m_Score == nullptr)
        {
            output += "Score: NULL\n";
            CLI_TRACE(output);
        }
        else
        {
            // output += "Score: " + m_Score->GetWins().to_string() + "W | " + m_Score->GetLosses() + " L (" + m_Score->GetWinRate() + "%)\n";
            output += "Score: " + std::to_string(m_Score->GetWins()) + "W | " + std::to_string(m_Score->GetLosses()) + "L (" + std::to_string(m_Score->GetWinRate()) + "%)\n";
            CLI_TRACE(output);
        }
    }
}