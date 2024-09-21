//
// Created by ahues on 21/09/2024.
//

#include "GUI.h"

namespace PAG {
    GUI* GUI::_singleton = nullptr;

    GUI& GUI::getGUI() {
        if(!_singleton)
            _singleton = new GUI();
        return *_singleton;
    }

    GUI::GUI() {

    }

    GUI::~GUI() {

    }

    void GUI::init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    }

    void GUI::setMessage(const char* newMessage) {
        this->_messages = newMessage;
    }

    void GUI::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GUI::setWindowsPos(float x1, float y1, float x2, float y2, ImGuiCond_ flag1, ImGuiCond_ flag2) {
        _windowsPos = {x1, y1, x2, y2};
        _windowsFlags = {flag1, flag2};
    }

    void GUI::createWindows() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[0], _windowsPos[1]), _windowsFlags[0]);
        if(ImGui::Begin("Mensajes1")) { // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
                // Pintamos los controles
                ImGui::Text(this->_messages);
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End();


        ImGui::SetNextWindowPos(ImVec2(_windowsPos[2], _windowsPos[3]), _windowsFlags[1]);
        if(ImGui::Begin("Mensajes2")) { // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::Text(this->_messages);
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End();
    }


    void GUI::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI::freeResources() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
} // PAG