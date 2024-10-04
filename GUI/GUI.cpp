//
// Created by ahues on 21/09/2024.
//
#include "GUI.h"

#include <imgui_stdlib.h>

#define MAX_N_MESSAGES 150

#define MESSAGE_WIN_POS 0
#define COLOR_PICKER_WIN_POS 1
#define SHADER_LOADER_WIN_POS 2

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

    void GUI::setColorPickerWindowPos(float&& x, float&& y) {
        _windowsPos[COLOR_PICKER_WIN_POS * 2] = x;
        _windowsPos[COLOR_PICKER_WIN_POS * 2 + 1] = y;
    }

    void GUI::setMessagesWindowPos(float&& x, float&& y) {
        _windowsPos[MESSAGE_WIN_POS * 2] = x;
        _windowsPos[MESSAGE_WIN_POS * 2 + 1] = y;
    }

    void GUI::setShaderLoaderWindowPos(float&& x, float&& y) {
        _windowsPos[SHADER_LOADER_WIN_POS * 2] = x;
        _windowsPos[SHADER_LOADER_WIN_POS * 2 + 1] = y;
    }

    void GUI::setColorPickerWindowSize(float&& w, float&& h) {
        _windowsSize[COLOR_PICKER_WIN_POS * 2] = w;
        _windowsSize[COLOR_PICKER_WIN_POS * 2 + 1] = h;
    }

    void GUI::setMessagesWindowSize(float&& w, float&& h) {
        _windowsSize[MESSAGE_WIN_POS * 2] = w;
        _windowsSize[MESSAGE_WIN_POS * 2 + 1] = h;
    }

    void GUI::setShaderLoaderWindowSize(float&& w, float&& h) {
        _windowsSize[SHADER_LOADER_WIN_POS * 2] = w;
        _windowsSize[SHADER_LOADER_WIN_POS * 2 + 1] = h;
    }

    void GUI::colorPickerWindow() {
        //Inicializamos siguiente ventana
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[COLOR_PICKER_WIN_POS * 2], _windowsPos[COLOR_PICKER_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Fondo")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[2],_windowsSize[3]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale (1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::ColorPicker4("Actual", (float*)&_color,
                                ImGuiColorEditFlags_PickerHueWheel |
                                ImGuiColorEditFlags_DisplayRGB |
                                ImGuiColorEditFlags_DisplayHSV |
                                ImGuiColorEditFlags_DisplayHex
                                | ImGuiColorEditFlags_NoAlpha);
        }
        ImGui::End();
    }

    void GUI::messageWindow() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[MESSAGE_WIN_POS * 2], _windowsPos[MESSAGE_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Mensajes")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale (1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles

            while(_messages.size() > MAX_N_MESSAGES)
                _messages.pop_front();

            for(auto message : _messages) {
                ImGui::Text(message.c_str());
            }
        }
        ImGui::End();
    }

    void GUI::shaderLoaderWindow() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[SHADER_LOADER_WIN_POS * 2], _windowsPos[SHADER_LOADER_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Shader loader")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles

            ImGui::InputText("##", &_shaderName, ImGuiInputTextFlags_AutoSelectAll);
            if(ImGui::Button("Load"))
                _buttonState = true;
        }
        ImGui::End();
    }

    void GUI::createWindows() {
        messageWindow();
        colorPickerWindow();
        shaderLoaderWindow();
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

    ImVec4 GUI::getColor() {
        return _color;
    }

    void GUI::setColor(float x, float y, float z, float w) {
        _color = ImVec4(x, y, z, w);
    }

    bool GUI::getButtonState() {
        return _buttonState;
    }

    void GUI::setButtonState(bool buttonState) {
        _buttonState = buttonState;
    }

    std::string GUI::getShaderName() {
        return _shaderName;
    }
} // PAG