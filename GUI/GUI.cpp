//
// Created by ahues on 21/09/2024.
//
#include "GUI.h"

#define MAX_N_MESSAGES 30

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

    void GUI::addMessage(const std::string& newMessage) {
        this->_messages.push_back(newMessage);
    }

    void GUI::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GUI::setWindowsPos(float&& x1, float&& y1, float&& x2, float&& y2) {
        _windowsPos = {x1, y1, x2, y2};
    }

    void GUI::setWindowsSize(float&& w1, float&& h1, float&& w2, float&& h2) {
        _windowsSize = {w1, h1, w2, h2};
    }

    void GUI::createWindows() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[0], _windowsPos[1]), ImGuiCond_Always);
        if(ImGui::Begin("Mensajes")) { // La ventana está desplegada
            ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::SetWindowFontScale (1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            while(_messages.size() > MAX_N_MESSAGES)
                _messages.pop_front();

            for(auto message : _messages) {
                ImGui::Text(message.c_str());
            }
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End();
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[2], _windowsPos[3]), ImGuiCond_Always);
        if(ImGui::Begin("Mensajes2")) { // La ventana está desplegada
            ImGui::SetWindowSize(ImVec2(_windowsSize[2],_windowsSize[3]), ImGuiWindowFlags_NoMove);
            ImGui::SetWindowFontScale (1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::SetNextItemWidth(100.0f);
            ImVec4 a(0.5f, 0.0f, 0.0f, 1.0f);
            ImGui::ColorPicker3("##MyColor##6", (float*)&a,
                                ImGuiColorEditFlags_PickerHueWheel |
                                    ImGuiColorEditFlags_NoSidePreview |
                                    ImGuiColorEditFlags_NoInputs |
                                    ImGuiColorEditFlags_NoAlpha);
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