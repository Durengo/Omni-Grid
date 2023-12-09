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
        unsigned int m_Wins;
        unsigned int m_Losses;
        float m_WinRate;

        // Constructors & Destructors
    public:
        Score();
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