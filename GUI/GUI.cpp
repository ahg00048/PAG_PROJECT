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

    void GUI::setWindow(float x, float y, ImGuiCond_ flag) {
        ImGui::SetNextWindowPos(ImVec2(x, y), flag);
    }

    void GUI::setMessage(const char* newMessage) {
        this->_messages = newMessage;
    }

    void GUI::createWindow() {
        if(ImGui::Begin("Mensajes")) { // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::Text(this->_messages);
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End();
    }

    void GUI::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
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