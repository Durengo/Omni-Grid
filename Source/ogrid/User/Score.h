#pragma once

#include <string>

/**
 * @file Score.h
 * @brief Contains the Score class
 * @date 2023-12-09
 */
namespace OGRID
{
    /**
     * @brief The Score class
     * @details This class is used to manage the score and interact with the database
     * @date 2023-12-09
     */
    class Score
    {
    private:
        /**
         * @brief The Score Id
         * @date 2023-12-09
         */
        // Primary key
        unsigned int m_ScoreId;

        /**
         * @brief The User Id
         * @date 2023-12-09
         */
        // Foreign key
        unsigned int m_UserId;

        /**
         * @brief The number of wins
         * @date 2023-12-09
         */
        unsigned int m_Wins;

        /**
         * @brief The number of losses
         * @date 2023-12-09
         */
        unsigned int m_Losses;

        /**
         * @brief The win rate
         * @date 2023-12-09
         */
        double m_WinRate;

        // Constructors & Destructors
    public:
        /**
         * @brief Construct a new Score object
         * @date 2023-12-09
         */
        Score();

        /**
         * @brief Construct a new Score object
         * @date 2023-12-09
         * @param scoreId The score id
         * @param userId The user id
         * @param wins The number of wins
         * @param losses The number of losses
         * @param winRate The win rate
         */
        Score(unsigned int scoreId = 0, unsigned int userId = 0, unsigned int wins = 0, unsigned int losses = 0, double winRate = 0.0);

        /**
         * @brief Destroy the Score object
         * @date 2023-12-09
         */
        ~Score();

        // Getters & Setters
    public:
        /**
         * @brief Get the Score Id
         * @date 2023-12-09
         * @return The score id
         */
        unsigned int GetWins() const;

        /**
         * @brief Set the Score Id
         * @date 2023-12-09
         * @param scoreId The score id
         */
        void SetWins(unsigned int wins);

        /**
         * @brief Get the User Id
         * @date 2023-12-09
         * @return The user id
         */
        unsigned int GetLosses() const;

        /**
         * @brief Set the User Id
         * @date 2023-12-09
         * @param userId The user id
         */
        void SetLosses(unsigned int losses);

        /**
         * @brief Get the number of wins
         * @date 2023-12-09
         * @return The number of wins
         */
        double GetWinRate() const;

        /**
         * @brief Set the number of wins
         * @date 2023-12-09
         * @param wins The number of wins
         */
        void SetWinRate(double winRate);

        // Private methods
    private:
        /**
         * @brief Calculate the win rate
         * @date 2023-12-09
         */
        void CalculateWinRate();

        // Methods
    public:
        /**
         * @brief Add a win
         * @date 2023-12-09
         */
        void AddWin();

        /**
         * @brief Add a loss
         * @date 2023-12-09
         */
        void AddLoss();
    };
}