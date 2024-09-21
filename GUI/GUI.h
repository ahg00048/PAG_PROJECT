//
// Created by ahues on 21/09/2024.
//

#ifndef PAG_PROJECT_GUI_H
#define PAG_PROJECT_GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace PAG {
    class GUI {
    private:
        static GUI* _singleton;
        const char* _messages;
        GUI();
    public:
        ~GUI();
        static GUI& getGUI();
        void init();
        void newFrame();
        void render();
        void setMessage(const char* newMessage);
        void setWindow(float x, float y, ImGuiCond_ flag);
        void freeResources();
        void createWindow();
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
