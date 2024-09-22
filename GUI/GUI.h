//
// Created by ahues on 21/09/2024.
//

#ifndef PAG_PROJECT_GUI_H
#define PAG_PROJECT_GUI_H

#include <array>
#include <deque>
#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace PAG {
    class GUI {
    private:
        static GUI* _singleton;
        std::deque<std::string> _messages;
        //window properties
        std::array<float, 4> _windowsPos;
        std::array<float, 4> _windowsSize;
        GUI();
    public:
        ~GUI();
        static GUI& getGUI();
        void init();
        void newFrame();
        void render();
        void addMessage(const std::string& newMessage);
        void freeResources();
        void setWindowsPos(float&& x1, float&& y1, float&& x2, float&& y2);
        void setWindowsSize(float&& w1, float&& h1, float&& w2, float&& h2);
        void createWindows();
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
