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
    // Forward declaration
    class Score;

    class User
    {
    private:
        // Primary key
        unsigned int m_UserId;

        std::string m_UserName;
        std::string m_UserPassword;
        std::string m_UserFirstName;
        std::string m_UserLastName;

        Score *m_Score;

        // Constructors & Destructors
    public:
        User();
        User(int userId, std::string userName, std::string userPassword, std::string userFirstName = "", std::string userLastName = "", Score *score = nullptr);
        ~User();

        // Getters & Setters
    public:
        unsigned int GetUserId() const;
        void SetUserId(unsigned int userId);

        std::string GetUserName() const;
        void SetUserName(const std::string &userName);

        std::string GetUserPassword() const;
        void SetUserPassword(const std::string &userPassword);

        std::string GetUserFirstName() const;
        void SetUserFirstName(const std::string &userFirstName);

        std::string GetUserLastName() const;
        void SetUserLastName(const std::string &userLastName);

        Score *GetScore() const;
        void SetScore(Score *score);

        // Methods
    public:
        void Display() const;
    };
}