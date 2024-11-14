//
// Created by ahues on 21/09/2024.
//
#include "GUI.h"

#include <imgui_stdlib.h>

#define MAX_N_MESSAGES 150

#define MESSAGE_WIN_POS 0
#define COLOR_PICKER_WIN_POS 1
#define SHADER_LOADER_WIN_POS 2
#define CAMERA_WIN_POS 3
#define FILE_EXPLORER_WIN_POS 4
#define MODEL_MOVE_SET_WIN_POS 5

namespace PAG {
    GUI* GUI::_singleton = nullptr;

    GUI& GUI::getGUI() {
        if(!_singleton)
            _singleton = new GUI();
        return *_singleton;
    }

    GUI::GUI() {
        _fileExplorer.SetTitle("File explorer");
        _fileExplorer.SetTypeFilters({".obj"});
    }

    GUI::~GUI() {

    }

    void GUI::selectCameraMove(const std::string& move) {
        if(move == "Tilt")
            _cameraSelectedMove = CameraMove::TILT;
        else if(move == "Pan")
            _cameraSelectedMove = CameraMove::PAN;
        else if(move == "Crane")
            _cameraSelectedMove = CameraMove::CRANE;
        else if(move == "Dolly")
            _cameraSelectedMove = CameraMove::DOLLY;
        else if(move == "Orbit")
            _cameraSelectedMove = CameraMove::ORBIT;
        else if(move == "Zoom")
            _cameraSelectedMove = CameraMove::ZOOM;
    }

    void GUI::selectModelMove(const std::string& move) {
        if(move == "Translation")
            _modelMove = ModelMove::translation;
        else if(move == "Rotation")
            _modelMove = ModelMove::rotation;
        else if(move == "Scale")
            _modelMove = ModelMove::scale;
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

    void GUI::setCameraWindowPos(float &&x, float &&y) {
        _windowsPos[CAMERA_WIN_POS * 2] = x;
        _windowsPos[CAMERA_WIN_POS * 2 + 1] = y;
    }

    void GUI::setModelMoveSetWindowPos(float &&x, float &&y) {
        _windowsPos[MODEL_MOVE_SET_WIN_POS * 2] = x;
        _windowsPos[MODEL_MOVE_SET_WIN_POS * 2 + 1] = y;
    }

    void GUI::setFileExplorerWindowPos(float &&x, float &&y) {
        _windowsPos[FILE_EXPLORER_WIN_POS * 2] = x;
        _windowsPos[FILE_EXPLORER_WIN_POS * 2 + 1] = y;

        _fileExplorer.SetWindowPos(x, y);
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

    void GUI::setCameraWindowSize(float &&w, float &&h) {
        _windowsSize[CAMERA_WIN_POS * 2] = w;
        _windowsSize[CAMERA_WIN_POS * 2 + 1] = h;
    }

    void GUI::setModelMoveSetWindowSize(float &&w, float &&h) {
        _windowsSize[MODEL_MOVE_SET_WIN_POS * 2] = w;
        _windowsSize[MODEL_MOVE_SET_WIN_POS * 2 + 1] = h;
    }

    void GUI::setFileExplorerWindowSize(float &&w, float &&h) {
        _windowsSize[FILE_EXPLORER_WIN_POS * 2] = w;
        _windowsSize[FILE_EXPLORER_WIN_POS * 2 + 1] = h;

        _fileExplorer.SetWindowSize(w, h);
    }

    void GUI::colorPickerWindow() {
        //Inicializamos siguiente ventana
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[COLOR_PICKER_WIN_POS * 2], _windowsPos[COLOR_PICKER_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Background")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[2],_windowsSize[3]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale (1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::ColorPicker4("picked", (float*)&_color,
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
        if(ImGui::Begin("Messages")) { // La ventana está desplegada
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
                _shaderButtonState = true;
        }
        ImGui::End();
    }

    void GUI::modelMoveSetWindow() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[SHADER_LOADER_WIN_POS * 2], _windowsPos[SHADER_LOADER_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Model")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            ImGui::Text("Selected Model: ");

            for(int i = 0; i < _numberModels; i++) {
                if(ImGui::Button(std::to_string(i).c_str()))
                    _selectedModel = i;

                ImGui::SameLine();

                if(i == _numberModels - 1)
                    if(ImGui::Button("Destroy Model"))
                        _destroySelectedModel = true;
            }

            ImGui::Separator();
            if(_selectedModel != -1) {
                ImGui::Columns(2);
                moveConfigSubWindow();
                ImGui::NextColumn();
                materialSubWindow();
                ImGui::NextColumn();
                ImGui::Columns(1);
                ImGui::Separator();
            }
        }
        ImGui::End();
    }

    void GUI::fileExplorerWindow() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[FILE_EXPLORER_WIN_POS * 2], _windowsPos[FILE_EXPLORER_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("File explorer")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            if(ImGui::Button("Create model with .obj file"))
                _fileExplorer.Open();
        }
        ImGui::End();
    }

    void GUI::cameraWindow() {
        ImGui::SetNextWindowPos(ImVec2(_windowsPos[CAMERA_WIN_POS * 2], _windowsPos[CAMERA_WIN_POS * 2 + 1]), ImGuiCond_Once);
        if(ImGui::Begin("Camera")) { // La ventana está desplegada
            //ImGui::SetWindowSize(ImVec2(_windowsSize[0],_windowsSize[1]), ImGuiWindowFlags_None);
            ImGui::SetWindowFontScale(1.0f); // Escalamos el texto si fuera necesario
            // Pintamos los controles
            const char* cameraMoveStr[] = {"Tilt","Pan","Crane", "Dolly", "Orbit", "Zoom"};
            size_t cameraNumberMoves = 6;
            static unsigned int moveSelected = 0;

            ImGui::Text("Camera movement: "); ImGui::SameLine();
            if(ImGui::BeginCombo("##", cameraMoveStr[moveSelected], ImGuiComboFlags_HeightLargest | ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview)) {
                for(int i = 0; i < cameraNumberMoves; i++) {
                    const bool selected = (moveSelected == i);
                    if(ImGui::Selectable(cameraMoveStr[i], selected)) {
                        moveSelected = i;
                        selectCameraMove(cameraMoveStr[moveSelected]);
                    }

                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::SameLine();
            ImGui::Checkbox("Perspective projection ", &_cameraPerspProjection);

            switch(_cameraSelectedMove) {
                case CameraMove::TILT:
                    tiltSetup();
                    break;
                case CameraMove::PAN:
                    panSetup();
                    break;
                case CameraMove::CRANE:
                    craneSetup();
                    break;
                case CameraMove::DOLLY:
                    dollySetup();
                    break;
                case CameraMove::ORBIT:
                    orbitSetup();
                    break;
                case CameraMove::ZOOM:
                    zoomSetup();
            }
        }

        ImGui::End();
    }

    void GUI::materialSubWindow() {
        ImGui::Text("Model Material:");

    }

    void GUI::moveConfigSubWindow() {
        const char* MovesStr[] = {"Translation","Rotation","Scale"};
        size_t numberMoves = 3;
        static unsigned int moveSelected = 0;

        ImGui::Text("Model Transformation:");
        if(ImGui::BeginCombo("##", MovesStr[moveSelected], ImGuiComboFlags_HeightLargest | ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview)) {
            for(int i = 0; i < numberMoves; i++) {
                const bool selected = (moveSelected == i);
                if(ImGui::Selectable(MovesStr[i], selected)) {
                    moveSelected = i;
                    selectModelMove(MovesStr[moveSelected]);
                }

                if(selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        switch(_modelMove) {
            case ModelMove::translation:
                translationSetup();
                break;
            case ModelMove::rotation:
                rotationSetup();
                break;
            case ModelMove::scale:
                scaleSetup();
        }
    }

    void GUI::translationSetup() {
        ImVec2 buttonSize(80, 20);

        if (ImGui::Button("UP", buttonSize))
            _modelMoveDirection = move1;
        ImGui::SameLine();
        if (ImGui::Button("DOWN", buttonSize))
            _modelMoveDirection = move2;
        if (ImGui::Button("LEFT", buttonSize))
            _modelMoveDirection = move3;
        ImGui::SameLine();
        if (ImGui::Button("RIGHT", buttonSize))
            _modelMoveDirection = move4;
        if (ImGui::Button("FORWARD", buttonSize))
            _modelMoveDirection = move5;
        ImGui::SameLine();
        if (ImGui::Button("BACKWARD", buttonSize))
            _modelMoveDirection = move6;
    }

    void GUI::rotationSetup() {
        ImVec2 buttonSize(140, 20);

        ImGui::Text("Rotation X axis");
        if (ImGui::Button("CLOCKWISE##01", buttonSize))
            _modelMoveDirection = move1;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##01", buttonSize))
            _modelMoveDirection = move2;

        ImGui::Text("Rotation Y axis");
        if (ImGui::Button("CLOCKWISE##02", buttonSize))
            _modelMoveDirection = move3;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##02", buttonSize))
            _modelMoveDirection = move4;

        ImGui::Text("Rotation Z axis");
        if (ImGui::Button("CLOCKWISE##03", buttonSize))
            _modelMoveDirection = move5;
        ImGui::SameLine();
        if (ImGui::Button("COUNTER CLOCKWISE##03", buttonSize))
            _modelMoveDirection = move6;
    }

    void GUI::scaleSetup() {
        ImVec2 buttonSize(100, 20);

        ImGui::Text("Scale in X axis");
        if (ImGui::Button("INCREASE##01", buttonSize))
            _modelMoveDirection = move1;
        ImGui::SameLine();
        if (ImGui::Button("DECREASE##01", buttonSize))
            _modelMoveDirection = move2;

        ImGui::Text("Scale in Y axis");
        if (ImGui::Button("INCREASE##02", buttonSize))
            _modelMoveDirection = move3;
        ImGui::SameLine();
        if (ImGui::Button("DECREASE##02", buttonSize))
            _modelMoveDirection = move4;

        ImGui::Text("Scale in Z axis");
        if (ImGui::Button("INCREASE##03", buttonSize))
            _modelMoveDirection = move5;
        ImGui::SameLine();
        if (ImGui::Button("DECREASE##03", buttonSize))
            _modelMoveDirection = move6;
    }

    void GUI::orbitSetup() {
        ImVec2 buttonSize(80, 20);

        if (ImGui::Button("UP", buttonSize))
            _cameraMoveDirection = uMove;
        ImGui::SameLine();
        if (ImGui::Button("DOWN", buttonSize))
            _cameraMoveDirection = dMove;
        if (ImGui::Button("LEFT", buttonSize))
            _cameraMoveDirection = lMove;
        ImGui::SameLine();
        if (ImGui::Button("RIGHT", buttonSize))
            _cameraMoveDirection = rMove;
    }

    void GUI::dollySetup() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("NORTH", buttonSize))
            _cameraMoveDirection = uMove;
        ImGui::SameLine();
        if(ImGui::Button("SOUTH", buttonSize))
            _cameraMoveDirection = dMove;
        if(ImGui::Button("WEST", buttonSize))
            _cameraMoveDirection = lMove;
        ImGui::SameLine();
        if(ImGui::Button("EAST", buttonSize))
            _cameraMoveDirection = rMove;
    }

    void GUI::tiltSetup() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("UP", buttonSize))
            _cameraMoveDirection = uMove;
        if(ImGui::Button("DOWN", buttonSize))
            _cameraMoveDirection = dMove;
    }

    void GUI::panSetup() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("LEFT", buttonSize))
            _cameraMoveDirection = lMove;
        ImGui::SameLine();
        if(ImGui::Button("RIGHT", buttonSize))
            _cameraMoveDirection = rMove;
    }

    void GUI::craneSetup() {
        ImVec2 buttonSize(80, 20);

        if(ImGui::Button("UP", buttonSize))
            _cameraMoveDirection = uMove;
        if(ImGui::Button("DOWN", buttonSize))
            _cameraMoveDirection = dMove;
    }

    void GUI::zoomSetup() {
        ImGui::SliderFloat("##xx", &_zoomScrollBar, MIN_FOV, MAX_FOV, "%.3f", ImGuiSliderFlags_None);
    }

    void GUI::createWindows() {
        messageWindow();
        colorPickerWindow();
        shaderLoaderWindow();
        cameraWindow();
        modelMoveSetWindow();
        fileExplorerWindow();
    }

    void GUI::render() {
        _fileExplorer.Display();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI::freeResources() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool GUI::captureMouse() {
        ImGuiIO& io = ImGui::GetIO();
        return io.WantCaptureMouse;
    }

    void GUI::resetCameraButtons() { _cameraMoveDirection = resetCamDir; }
    void GUI::resetModelButtons() { _modelMoveDirection = resetModDir; }

    void GUI::setColor(float x, float y, float z, float w) { _color = ImVec4(x, y, z, w); }
    void GUI::setShaderButtonState(bool buttonState) { _shaderButtonState = buttonState; }
    void GUI::setZoom(float zoom) { _zoomScrollBar = zoom; }

    ImVec4 GUI::getColor() const { return _color; }

    ModelMove GUI::getModelMove() const { return _modelMove; }
    ModelMoveDirection GUI::getModelMoveDirection() const { return _modelMoveDirection; }

    int GUI::getSelectedModel() const { return _selectedModel; }
    int GUI::getNumberModels() const { return _numberModels; }

    bool GUI::destroyModel() const { return _destroySelectedModel; }
    void GUI::resetDestroySelectedModelButton() { _destroySelectedModel = false; }

    void GUI::setSelectedModel(int selectedModel) { _selectedModel = selectedModel; }

    void GUI::setNumberModels(int numberModels) {
        _numberModels = numberModels;

        if(_numberModels <= 0)
            _selectedModel--;
    }

    bool GUI::ObjFileHasBeenSelected() const { return _fileExplorer.HasSelected(); }
    std::string GUI::getSelectedObjFile() { return _fileExplorer.GetSelected().string(); }
    void GUI::clearSelectedObjFile() { _fileExplorer.ClearSelected(); }

    bool GUI::getShaderButtonState() const { return _shaderButtonState; }
    const std::string& GUI::getShaderName() { return _shaderName; }

    CameraMove GUI::getCameraSelectedMove() const { return _cameraSelectedMove; }
    CameraMoveDirection GUI::getCameraMoveDirection() const { return _cameraMoveDirection; }
    bool GUI::getCameraPerspProjection() const { return _cameraPerspProjection; }

    float GUI::getZoom() const { return _zoomScrollBar; }
} // PAG