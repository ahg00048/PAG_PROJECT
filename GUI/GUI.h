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
        //windows properties
        std::array<float, 6> _windowsPos;
        std::array<float, 6> _windowsSize;

        ImVec4 _color;
        std::string _shaderFiles;

        GUI();

        void colorPickerWindow();
        void messageWindow();
        void shaderLoaderWindow();
    public:
        ~GUI();
        static GUI& getGUI();
        void init();
        void newFrame();
        void render();
        void addMessage(const std::string& newMessage);
        void freeResources();

        void setColorPickerWindowPos(float&& x, float&& y);
        void setMessagesWindowPos(float&& x, float&& y);
        void setShaderLoaderWindowPos(float&& x, float&& y);

        void setColorPickerWindowSize(float&& w, float&& h);
        void setMessagesWindowSize(float&& w, float&& h);
        void setShaderLoaderWindowSize(float&& w, float&& h);

        void createWindows();
        ImVec4 getColor();
        void setColor(float x, float y, float z, float w);
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
