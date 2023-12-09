#include "Score.h"

namespace OGRID
{
    // Constructors & Destructors

    Score::Score()
        : m_ScoreId(0), m_UserId(0), m_Wins(0), m_Losses(0), m_WinRate(0.0f)
    {
    }

    Score::Score(unsigned int scoreId, unsigned int userId, unsigned int wins, unsigned int losses, float winRate)
        : m_ScoreId(scoreId), m_UserId(userId), m_Wins(wins), m_Losses(losses), m_WinRate(winRate)
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