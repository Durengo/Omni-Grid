#pragma once

#include <functional>
#include <string>

#include <raylib.h>

/**
 * @file Button.h
 * @brief Button
 * @date 2023-12-06
 * @see https://www.raylib.com/

*/

namespace OGRID
{
    /**
     * @brief Button
     * @details This is a warpper around raylib's Rectangle and Color.
     * @date 2023-12-06
     * @see https://www.raylib.com/
     */
    struct Button
    {
        /**
         * @brief Bounds of the button.
         * @date 2023-12-06
         */
        // Position and dimensions of the button
        Rectangle bounds;

        /**
         * @brief Colors of the button.
         * @date 2023-12-06
         */
        // Color of the button when not interacted with
        Color normalColor;

        /**
         * @brief Colors of the button on mouse hover.
         * @date 2023-12-06
         */
        // Color of the button on mouse hover
        Color hoverColor;

        /**
         * @brief Colors of the button on mouse click.
         * @date 2023-12-06
         */
        // Color of the button when pressed
        Color pressedColor;

        /**
         * @brief Delegate function for button click event.
         * @date 2023-12-06
         */
        // Delegate function for button click event
        std::function<void()> onClick;

        /**
         * @brief Text to be displayed on the button.
         * @date 2023-12-06
         */
        // Text to be displayed on the button
        std::string text;

        /**
         * @brief Is the button enabled.
         * @date 2023-12-06
         */
        // Flag to enable or disable the button's click functionality
        bool isEnabled;

        /**
         * @brief Construct a new Button object.
         * @date 2023-12-06
         * @param bounds Bounds of the button.
         * @param normal Color of the button when not interacted with.
         * @param hover Color of the button on mouse hover.
         * @param pressed Color of the button when pressed.
         * @param clickCallback Delegate function for button click event.
         * @param text Text to be displayed on the button.
         * @param isEnabled Is the button enabled.
         */
        // Modify constructor to initialize isEnabled
        Button(Rectangle bounds, Color normal, Color hover, Color pressed, std::function<void()> clickCallback, std::string text = "Button", bool isEnabled = true)
            : bounds(bounds), normalColor(normal), hoverColor(hover), pressedColor(pressed), onClick(clickCallback), text(text), isEnabled(isEnabled) {}

        /**
         * @brief Update the button.
         * @date 2023-12-06
         */
        // Check if the button is hovered or clicked
        void Update()
        {
            if (isEnabled)
            {
                Vector2 mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, bounds))
                {
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        // Call the delegate function if the button is enabled
                        onClick();
                    }
                }
            }
        }

        /**
         * @brief Draw the button.
         * @date 2023-12-06
         */
        void Draw() const
        {
            Color currentColor = isEnabled ? normalColor : GRAY;

            if (CheckCollisionPointRec(GetMousePosition(), bounds))
            {
                currentColor = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? pressedColor : hoverColor;
            }
            DrawRectangleRec(bounds, currentColor);

            // Measure the text width and height
            int fontSize = 20;
            Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, 1);

            // Calculate text position to center it on the button
            float textX = bounds.x + (bounds.width - textSize.x) / 2;
            float textY = bounds.y + (bounds.height - textSize.y) / 2 - 10;

            // Adjust Y position to align text vertically in the middle
            textY += (textSize.y / 2);

            // Draw the text centered
            DrawText(text.c_str(), static_cast<int>(textX), static_cast<int>(textY), fontSize, WHITE);
        }

        /**
         * @brief Set the enabled state of the button.
         * @date 2023-12-06
         * @param enabled Is the button enabled.
         */
        void SetEnabled(bool enabled)
        {
            isEnabled = enabled;
        }
    };
}