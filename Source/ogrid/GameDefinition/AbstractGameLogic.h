#pragma once

#include <vector>

namespace OGRID
{
    class Grid;
    class Player;
    class MoveType;

    class AbstractGameLogic
    {
    protected:
        Grid *m_grid;
        std::vector<MoveType *> m_moveTypes;
        std::vector<Player *> m_players;
        Player *m_currentPlayer;

    public:
        AbstractGameLogic() : m_grid(nullptr), m_currentPlayer(nullptr) {}
        virtual ~AbstractGameLogic()
        {
            delete m_grid;
            for (auto moveType : m_moveTypes)
            {
                delete moveType;
            }
            for (auto player : m_players)
            {
                delete player;
            }
        }

    protected:
        virtual void InitializeGame() = 0;
        virtual void DeinitializeGame() = 0;

    public:
        virtual void MakeMove(Player &player) = 0;
        virtual void CheckConditions() = 0;
        virtual void ResetGame() = 0;
        virtual void EndGame() = 0;
    };
}