//
// Created by ahues on 21/09/2024.
//

#ifndef PAG_PROJECT_GUI_H
#define PAG_PROJECT_GUI_H

#include <array>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace PAG {
    class GUI {
    private:
        static GUI* _singleton;
        const char* _messages = "";
        std::array<float, 4> _windowsPos;
        std::array<ImGuiCond_, 2> _windowsFlags;
        GUI();
    public:
        ~GUI();
        static GUI& getGUI();
        void init();
        void newFrame();
        void render();
        void setMessage(const char* newMessage);
        void freeResources();
        void setWindowsPos(float x1, float y1, float x2, float y2, ImGuiCond_ flag1, ImGuiCond_ flag2);
        void createWindows();
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
