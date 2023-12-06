#include <gtest/gtest.h>

#include <durlib.h>

#include "GameLogicImplementation/GameConfiguration.h"

namespace OGRID
{
    class GameConfigurationBuilderTest : public ::testing::Test
    {
    protected:
        GameConfigurationBuilder *builder;

        void SetUp() override
        {
            builder = new GameConfigurationBuilder();
            builder->setGameName("Chess");
            builder->setGameDescription("T1");
            builder->setGrid(8, 8);
            Player *player1 = new Player("Alice");
            Player *player2 = new Player("Bob");
            builder->addPlayer(player1);
            builder->addPlayer(player2);
            builder->setMaxPlayers(2);
        }

        void TearDown() override
        {
            delete builder;
        }
    };

    TEST_F(GameConfigurationBuilderTest, SetGameName)
    {
        // All values must be set otherwise build() will throw an exception
        GameConfiguration *config = builder->build();
        EXPECT_EQ(config->gameName, "Chess");
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, SetGameDescription)
    {
        builder->setGameDescription("A classic game");
        GameConfiguration *config = builder->build();
        EXPECT_EQ(config->gameDescription, "A classic game");
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, SetGrid)
    {
        builder->setGrid(8, 8);
        GameConfiguration *config = builder->build();
        EXPECT_NE(config->grid, nullptr);
        EXPECT_EQ(config->grid->GetRows(), 8);
        EXPECT_EQ(config->grid->GetCols(), 8);
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, SetMaxPlayers)
    {
        builder->setMaxPlayers(4);
        GameConfiguration *config = builder->build();
        EXPECT_EQ(config->maxPlayers, 4);
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, AddPlayer)
    {
        GameConfiguration *config = builder->build();
        EXPECT_EQ(config->players.size(), 2);
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, PlayerNameAndPtrPairing)
    {
        Player *player = new Player("Charlie");
        builder->addPlayer(player);
        builder->setMaxPlayers(3);
        GameConfiguration *config = builder->build();
        EXPECT_FALSE(config->playerPairs.empty());
        EXPECT_EQ(config->playerPairs[2].name, "Charlie");
        EXPECT_EQ(config->playerPairs[2].ptr, player);
        delete player;
        delete config;
    }

    TEST_F(GameConfigurationBuilderTest, PlayerNameAndPtrVecToStringT)
    {
        std::vector<PlayerNameAndPtr> playerPairs = {
            {"Alice", nullptr},
            {"Bob", nullptr}};
        std::string actual = PlayerNameAndPtrVecToString(playerPairs);
        std::string expect = "Alice [0x0]\nBob [0x0]";

        EXPECT_EQ(actual, expect);
    }

    TEST_F(GameConfigurationBuilderTest, CompleteBuild)
    {
        GameConfigurationBuilder builder;
        GameConfiguration *config = builder
                                        .setGameName("Chess")
                                        .setGameDescription("A classic game")
                                        .setGrid(8, 8)
                                        .setMaxPlayers(2)
                                        .addPlayer(new Player("Alice"))
                                        .addPlayer(new Player("Bob"))
                                        .build();

        EXPECT_EQ(config->gameName, "Chess");
        EXPECT_EQ(config->gameDescription, "A classic game");
        EXPECT_EQ(config->maxPlayers, 2);
        EXPECT_EQ(config->players.size(), 2);

        // Clean up
        delete config->grid;
        for (auto player : config->players)
        {
            delete player;
        }
        delete config;
    }

}

int main(int argc, char **argv)
{
    DURLIB::Log::Init();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}