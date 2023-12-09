#pragma once

#include <string>

#include "Player/Player.h"

/**
 * @file User.h
 * @brief Contains the User class
 * @date 2023-12-09
 */
namespace OGRID
{
    // Forward declaration
    class Score;

    /**
     * @brief The User class
     * @details This class is used to manage the user and interact with the database
     * @date 2023-12-09
     * @see Score
     */
    class User
    {
    private:
        /**
         * @brief The Score Id
         * @date 2023-12-09
         */
        // Primary key
        unsigned int m_UserId;

        /**
         * @brief The User name
         * @date 2023-12-09
         */
        std::string m_UserName;

        /**
         * @brief The User password
         * @date 2023-12-09
         */
        std::string m_UserPassword;

        /**
         * @brief The User first name
         * @date 2023-12-09
         */
        std::string m_UserFirstName;

        /**
         * @brief The User last name
         * @date 2023-12-09
         */
        std::string m_UserLastName;

        /**
         * @brief The User score
         * @date 2023-12-09
         */
        Score *m_Score;

        /**
         * @brief The User player
         * @date 2023-12-09
         */
        Player *m_Player;

        // Constructors & Destructors
    public:
        /**
         * @brief Construct a new User object
         * @date 2023-12-09
         */
        User();

        /**
         * @brief Construct a new User object
         * @date 2023-12-09
         * @param userId The User Id
         * @param userName The User name
         * @param userPassword The User password
         * @param userFirstName The User first name
         * @param userLastName The User last name
         * @param score The User score
         */
        User(int userId, std::string userName, std::string userPassword, std::string userFirstName = "", std::string userLastName = "", Score *score = nullptr);

        /**
         * @brief Destroy the User object
         * @date 2023-12-09
         */
        ~User();

        // Getters & Setters
    public:
        /**
         * @brief Get the User Id
         * @date 2023-12-09
         * @return The User Id
         */
        unsigned int GetUserId() const;

        /**
         * @brief Set the User Id
         * @date 2023-12-09
         * @param userId The User Id
         */
        void SetUserId(unsigned int userId);

        /**
         * @brief Get the User name
         * @date 2023-12-09
         * @return The User name
         */
        std::string GetUserName() const;

        /**
         * @brief Set the User name
         * @date 2023-12-09
         * @param userName The User name
         */
        void SetUserName(const std::string &userName);

        /**
         * @brief Get the User password
         * @date 2023-12-09
         * @return The User password
         */
        std::string GetUserPassword() const;

        /**
         * @brief Set the User password
         * @date 2023-12-09
         * @param userPassword The User password
         */
        void SetUserPassword(const std::string &userPassword);

        /**
         * @brief Get the User first name
         * @date 2023-12-09
         * @return The User first name
         */
        std::string GetUserFirstName() const;

        /**
         * @brief Set the User first name
         * @date 2023-12-09
         * @param userFirstName The User first name
         */
        void SetUserFirstName(const std::string &userFirstName);

        /**
         * @brief Get the User last name
         * @date 2023-12-09
         * @return The User last name
         */
        std::string GetUserLastName() const;

        /**
         * @brief Set the User last name
         * @date 2023-12-09
         * @param userLastName The User last name
         */
        void SetUserLastName(const std::string &userLastName);

        /**
         * @brief Get the User score
         * @date 2023-12-09
         * @return The User score
         */
        Score *GetScore() const;

        /**
         * @brief Set the User score
         * @date 2023-12-09
         * @param score The User score
         */
        void SetScore(Score *score);

        /**
         * @brief Get the User player
         * @date 2023-12-09
         * @return The User player
         */
        Player *GetPlayer() const;

        /**
         * @brief Set the User player
         * @date 2023-12-09
         * @param player The User player
         */
        void SetPlayer(Player *player);

        // Methods
    public:
        /**
         * @brief Displays the User
         * @details Shows the User Id, User name, User password, User first name, User last name, User score
         * @date 2023-12-09
         */
        void Display() const;

        /**
         * @brief Displays the User score
         * @details Shows only the User score
         * @date 2023-12-09
         */
        void DisplayScore() const;
    };
}