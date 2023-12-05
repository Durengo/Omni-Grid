#include <gtest/gtest.h>

#include <durlib.h>

#include "Player/Piece.h"

namespace OGRID
{
    // Test fixture for Piece
    class PieceTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    TEST_F(PieceTest, ConstructorInitialState)
    {
        Player *player = new Player("TestPlayer");
        Piece piece("K", player);
        EXPECT_EQ(piece.GetRepresentation(), "K");
        EXPECT_EQ(piece.GetOwner(), player);
        delete player;
    }

    // Move rules, attacks, etc. should be tested independently, i.e. create a unity test for each game.

    TEST_F(PieceTest, OwnerAssignmentRetrieval)
    {
        Player *player = new Player("TestPlayer");
        Piece piece("P", nullptr);
        piece.SetOwner(player);
        EXPECT_EQ(piece.GetOwner(), player);
        delete player;
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}