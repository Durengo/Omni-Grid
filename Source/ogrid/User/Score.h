#pragma once

#include <string>

/**
 * @file Score.h
 * @brief Contains the Score class
 * @date 2023-12-06
 */
namespace OGRID
{
    class Score
    {
    private:
        // Primary key
        unsigned int m_ScoreId;
        // Foreign key
        unsigned int m_UserId;

        unsigned int m_Wins;
        unsigned int m_Losses;
        double m_WinRate;

        // Constructors & Destructors
    public:
        Score();
        Score(unsigned int scoreId = 0, unsigned int userId = 0, unsigned int wins = 0, unsigned int losses = 0, double winRate = 0.0);
        ~Score();

        // Getters & Setters
    public:
        unsigned int GetWins() const;
        void SetWins(unsigned int wins);

        unsigned int GetLosses() const;
        void SetLosses(unsigned int losses);

        double GetWinRate() const;
        void SetWinRate(double winRate);

        // Private methods
    private:
        void CalculateWinRate();

        // Methods
    public:
        void AddWin();
        void AddLoss();
    };
}