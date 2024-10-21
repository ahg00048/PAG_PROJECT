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

#include "../Camara/Camera.h"

namespace PAG {
    class GUI {
    private:
        static GUI* _singleton;
        std::deque<std::string> _messages;
        //windows properties
        std::array<float, 8> _windowsPos;
        std::array<float, 8> _windowsSize;

        ImVec4 _color;
        std::string _shaderName;
        bool _shaderButtonState = false;

        CameraMove _cameraSelectedMove = CameraMove::TILT;
        bool _cameraPerspProjection = true;

        GUI();

        void selectCameraMove(const std::string& move);

        void colorPickerWindow();
        void messageWindow();
        void shaderLoaderWindow();
        void cameraWindow();
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
        void setCameraWindowPos(float&& x, float&& y);

        void setColorPickerWindowSize(float&& w, float&& h);
        void setMessagesWindowSize(float&& w, float&& h);
        void setShaderLoaderWindowSize(float&& w, float&& h);
        void setCameraWindowSize(float&& w, float&& h);

        void createWindows();

        ImVec4 getColor() const;
        void setColor(float x, float y, float z, float w);
        bool getShaderButtonState() const;
        void setShaderButtonState(bool buttonState);
        CameraMove getCameraSelectedMove() const;
        bool getCameraPerspProjection() const;
        std::string getShaderName();
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
