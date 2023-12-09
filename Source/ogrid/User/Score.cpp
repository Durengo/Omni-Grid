#include "Score.h"

namespace OGRID
{
    // Constructors & Destructors

    Score::Score()
        : m_Wins(0), m_Losses(0), m_WinRate(0.0f)
    {
    }

    Score::~Score()
    {
    }

    // Getters & Setters

    unsigned int Score::GetWins() const
    {
        return m_Wins;
    }

    void Score::SetWins(unsigned int wins)
    {
        m_Wins = wins;
    }

    unsigned int Score::GetLosses() const
    {
        return m_Losses;
    }

    void Score::SetLosses(unsigned int losses)
    {
        m_Losses = losses;
    }

    float Score::GetWinRate() const
    {
        return m_WinRate;
    }

    void Score::SetWinRate(float winRate)
    {
        m_WinRate = winRate;
    }
}