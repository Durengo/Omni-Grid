#include "Score.h"

namespace OGRID
{
    // Constructors & Destructors

    Score::Score()
        : m_ScoreId(0), m_UserId(0), m_Wins(0), m_Losses(0), m_WinRate(0.0)
    {
    }

    Score::Score(unsigned int scoreId, unsigned int userId, unsigned int wins, unsigned int losses, double winRate)
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

    double Score::GetWinRate() const
    {
        return m_WinRate;
    }

    void Score::SetWinRate(double winRate)
    {
        m_WinRate = winRate;
    }

    // Private methods

    void Score::CalculateWinRate()
    {
        m_WinRate = (double)m_Wins / (double)(m_Wins + m_Losses);
    }

    // Methods
    void Score::AddWin()
    {
        m_Wins++;
        CalculateWinRate();
    }

    void Score::AddLoss()
    {
        m_Losses++;
        CalculateWinRate();
    }
}