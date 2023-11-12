//
// Created by LastWeek on 12/11/2023.
//

#pragma once

#include <mutex>
#include <string>

//*************************************************************
//Can't have virtual static methods, so implement them yourself
//*************************************************************

namespace GENERICS{
    struct WindowResolution
    {
        int width;
        int height;
    };

    class iGUI {
    protected:
        std::string m_windowName;
        GENERICS::WindowResolution m_windowResolution;
        int m_targetFPS;
        float m_gridSize;
        float m_cellSize;
        float m_lineThickness;
        float m_margin;

    protected:
        ~iGUI() = default;
        iGUI() = default;

    public:
        virtual void InitializeWindow(std::string windowName, int screenWidth, int screenHeight, int targetFPS) = 0;
        virtual void BeginMainLoop() = 0;
    };
}


