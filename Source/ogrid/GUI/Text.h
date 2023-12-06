#pragma once

#include <string>

#include <raylib.h>

/**
 * @file Text.h
 * @brief Text
 * @date 2023-12-06
 * @see https://www.raylib.com/
 */

namespace OGRID
{
    /**
     * @brief Justify the text
     * @date 2023-12-06
     * @note This solution is not working as intended.
     */
    // Enumeration to specify text justification options
    enum class Justify
    {
        // No alignment, use x and y as is
        NONE,
        // Center the text horizontally on the screen
        CENTER_X,
        // Center the text vertically on the screen
        CENTER_Y,
        // Center the text both horizontally and vertically
        CENTER_BOTH
    };

    /**
     * @brief Text
     * @details This is a warpper around raylib's DrawTextEx.
     * @date 2023-12-06
     * @see https://www.raylib.com/
     */

    struct Text
    {
        /**
         * @brief Text to draw.
         * @date 2023-12-06
         */
        std::string text;

        /**
         * @brief Font size.
         * @date 2023-12-06
         */
        int fontSize;

        /**
         * @brief X position.
         * @date 2023-12-06
         */
        int x;

        /**
         * @brief Y position.
         * @date 2023-12-06
         */
        int y;

        /**
         * @brief Screen width.
         * @date 2023-12-06
         */
        int screenWidth;

        /**
         * @brief Screen height.
         * @date 2023-12-06
         */
        int screenHeight;

        /**
         * @brief Color of the text.
         * @date 2023-12-06
         */
        Color color;

        /**
         * @brief Justification of the text.
         * @date 2023-12-06
         */
        Justify justify;

        /**
         * @brief Construct a new Text object.
         * @date 2023-12-06
         * @param text Text to draw.
         * @param fontSize Font size.
         * @param x X position.
         * @param y Y position.
         * @param color Color of the text.
         * @param justify Justification of the text.
         * @param screenWidth Screen width.
         * @param screenHeight Screen height.
         */
        Text(std::string text, int fontSize, int x, int y, Color color, Justify justify = Justify::NONE, int screenWidth = 0, int screenHeight = 0)
            : text(text), fontSize(fontSize), x(x), y(y), color(color), justify(justify), screenWidth(screenWidth), screenHeight(screenHeight) {}

        /**
         * @brief Draw the text.
         * @date 2023-12-06
         */
        void Draw() const
        {
            int textX = x;
            int textY = y;

            // Only calculate text size if we need to justify it
            if (justify != Justify::NONE)
            {
                Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, 1);

                if (justify == Justify::CENTER_X || justify == Justify::CENTER_BOTH)
                {
                    textX = screenWidth / 2 - (textSize.x / 2);
                }

                if (justify == Justify::CENTER_Y || justify == Justify::CENTER_BOTH)
                {
                    textY = screenHeight / 2 - (textSize.y / 2);
                }
            }

            DrawText(text.c_str(), textX, textY, fontSize, color);
        }

        /**
         * @brief Set the text.
         * @date 2023-12-06
         * @param text Text to draw.
         */
        void SetText(std::string text)
        {
            this->text = text;
        }

        /**
         * @brief Set the screen size.
         * @date 2023-12-06
         * @param width Screen width.
         * @param height Screen height.
         */
        void SetScreenSize(int width, int height)
        {
            screenWidth = width;
            screenHeight = height;
        }

        /**
         * @brief Set the justification.
         * @date 2023-12-06
         * @param newJustify Justification of the text.
         */
        void SetJustification(Justify newJustify)
        {
            justify = newJustify;
        }
    };
}