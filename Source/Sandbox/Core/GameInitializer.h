#pragma once

/**
 * @file GameInitializer.h
 * @brief Game initializer
 * @date 2023-12-06
 */

// Forward declaration
namespace OGRID
{
    class User;
}
namespace Sandbox
{

    /**
     * @brief Game initializer
     * @date 2023-12-06
     */
    class GameInitializer
    {
    public:
        /**
         * @brief Starts the app and gives choice of games
         * @date 2023-12-06
         * @param user The user
         * @see GameWindow
         * @see User
         */
        // Starts the app and gives choice of games
        static void Start(OGRID::User *user);
    };
}