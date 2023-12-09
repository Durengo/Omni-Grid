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
        float m_WinRate;

        // Constructors & Destructors
    public:
        Score();
        Score(unsigned int scoreId = 0, unsigned int userId = 0, unsigned int wins = 0, unsigned int losses = 0, float winRate = 0.0f);
        ~Score();

        // Getters & Setters
    public:
        unsigned int GetWins() const;
        void SetWins(unsigned int wins);

        unsigned int GetLosses() const;
        void SetLosses(unsigned int losses);

        float GetWinRate() const;
        void SetWinRate(float winRate);
    };
}