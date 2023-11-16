#include "TicTacToeDefinition.h"

#include "CoreMoveRules.h"
#include "CoreDefinitions/MoveDefinitions.h"
#include "CoreDefinitions/PlayerDefinitions.h"

namespace OGRID
{
    TicTacToeDefinition::TicTacToeDefinition()
    {
        InitializeGame();
    }
    TicTacToeDefinition::~TicTacToeDefinition()
    {
        DeinitializeGame();
    }

    // Private methods
    void TicTacToeDefinition::InitializeGame()
    {
        this->m_moveTypes = OGRID::GetTicTacToeMoveTypes();
        this->m_players = OGRID::GetTicTacToePlayers(this->m_moveTypes);
        this->m_grid = new Grid(3, 3);
    }
    void TicTacToeDefinition::DeinitializeGame()
    {
    }

    // Public methods
    void TicTacToeDefinition::MakeMove(Player &player)
    {
    }

    void TicTacToeDefinition::CheckConditions()
    {
    }

    void TicTacToeDefinition::ResetGame()
    {
    }

    void TicTacToeDefinition::EndGame()
    {
    }
}