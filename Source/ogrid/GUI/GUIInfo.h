#pragma once

#include <string>

/**
 * @file GUIInfo.h
 * @brief GUI info
 * @date 2023-12-06
 */

/**
 * @brief GUI info
 * @details Contains information about the GUI.
 * This is mostly used for the raylib window
 * but it has core information for drawing buttons and texts.
 * @date 2023-12-06
 * @see https://www.raylib.com/
 * @see Button
 * @see Text
 * @note This provides the core information for the raylib window.
 */
struct GUIInfo
{
    /**
     * @brief Width of the window.
     * @date 2023-12-06
     */
    int width;

    /**
     * @brief Height of the window.
     * @date 2023-12-06
     */
    int height;

    /**
     * @brief Title of the window.
     * @date 2023-12-06
     */
    std::string windowName;

    /**
     * @brief Target FPS.
     * @date 2023-12-06
     */
    int targetFPS;

    /**
     * @brief Cell size.
     * @date 2023-12-06
     */
    float cellSize;

    /**
     * @brief Line thickness.
     * @date 2023-12-06
     */
    float lineThickness;

    /**
     * @brief Margin.
     * @date 2023-12-06
     */
    float margin;
};
