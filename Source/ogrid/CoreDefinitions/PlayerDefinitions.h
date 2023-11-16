#pragma once

#include <vector>

namespace OGRID
{
    class Player;
    class MoveType;

    std::vector<Player *> GetTicTacToePlayers(std::vector<MoveType *> &moveTypes);
}