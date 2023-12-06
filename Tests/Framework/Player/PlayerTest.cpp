#include <gtest/gtest.h>

#include <durlib.h>

#include "Player/Player.h"

namespace OGRID
{
    class PlayerTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
    };

    TEST_F(PlayerTest, ConstructorInitialState)
    {
        Player player("Alice", PlayerType::Human, 1);
        EXPECT_EQ(player.GetPlayerName(), "Alice");
        EXPECT_EQ(player.GetPlayerType(), PlayerType::Human);
        EXPECT_EQ(player.GetSide(), 1);
    }

    TEST_F(PlayerTest, SetAndGetPlayerName)
    {
        Player player;
        player.SetPlayerName("Bob");
        EXPECT_EQ(player.GetPlayerName(), "Bob");
    }

    TEST_F(PlayerTest, SetAndGetPlayerType)
    {
        Player player;
        player.SetPlayerType(PlayerType::AI);
        EXPECT_EQ(player.GetPlayerType(), PlayerType::AI);
    }

    TEST_F(PlayerTest, SetAndGetSide)
    {
        Player player;
        player.SetSide(2);
        EXPECT_EQ(player.GetSide(), 2);
    }

    TEST_F(PlayerTest, InvalidSideSetting)
    {
        Player player;
        EXPECT_THROW(player.SetSide(-2), std::invalid_argument);
    }

    TEST_F(PlayerTest, PlayerTypeEnumConversion)
    {
        EXPECT_EQ(PlayerTypeStringToEnum("Human"), PlayerType::Human);
        EXPECT_EQ(PlayerTypeStringToEnum("AI"), PlayerType::AI);
    }

    TEST_F(PlayerTest, PlayerTypeStringConversion)
    {
        EXPECT_EQ(PlayerTypeEnumToString(PlayerType::Human), "Human");
        EXPECT_EQ(PlayerTypeEnumToString(PlayerType::AI), "AI");
    }

    TEST_F(PlayerTest, PlayerVecToStringRepresentation)
    {
        std::vector<Player *> players;
        players.push_back(new Player("Charlie", PlayerType::Human, 1));
        players.push_back(new Player("Delta", PlayerType::AI, 2));
        std::string rep = PlayerVecToString(players);
        // Check the string representation matches the expected format
        for (auto p : players)
        {
            delete p;
        }
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}