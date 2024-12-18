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
#include "../vendor/imfilebrowser.h"

namespace PAG {
    enum CameraMoveDirection {
        lMove = 0,
        rMove,
        uMove,
        dMove,
        resetCamDir
    };

    enum ModelMoveDirection {
        move1 = 0,
        move2,
        move3,
        move4,
        move5,
        move6,
        resetModDir
    };

    enum ModelMove {
        translation = 0,
        rotation,
        scale
    };

    class GUI {
    private:
        static GUI* _singleton;
        std::deque<std::string> _messages;
        //windows properties
        std::array<float, 16> _windowsPos;
        std::array<float, 16> _windowsSize;

        ImVec4 _color;
        std::string _shaderName;
        bool _shaderButtonState = false;

        CameraMove _cameraSelectedMove = CameraMove::TILT;
        bool _cameraPerspProjection = true;
        float _zoomScrollBar = MIN_FOV;
        CameraMoveDirection _cameraMoveDirection = resetCamDir;

        ModelMoveDirection _modelMoveDirection = resetModDir;
        ModelMove _modelMove = translation;
        int _numberModels = 0;
        int _selectedModel = -1;
        bool _destroySelectedModel = false;

        int _numberLights = 0;
        int _selectedLight = -1;

        ImGui::FileBrowser _fileExplorer;

        float _diffSettings[3];
        float _ambSettings[3];
        float _specSettings[3];
        float _phongExpSettings;

        bool _triangleMesh = false;

        float _lDiffSettings[3];
        float _lAmbSettings[3];
        float _lSpecSettings[3];
        float _gammaSettings;
        float _s;

        GUI();

        void selectCameraMove(const std::string& move);
        void selectModelMove(const std::string& move);

        void colorPickerWindow();
        void messageWindow();
        void shaderLoaderWindow();
        void cameraWindow();
        void modelMoveSetWindow();
        void fileExplorerWindow();
        void lightingWindow();
        void rendererWindow();

        void translationSetup();
        void rotationSetup();
        void scaleSetup();

        void materialSubWindow();
        void moveConfigSubWindow();

        void orbitSetup();
        void dollySetup();
        void tiltSetup();
        void panSetup();
        void craneSetup();
        void zoomSetup();

        void SpotLightSetup();
        void pointLightDirLightSetup();
        void ambientLightSetup();
    public:
        ~GUI();
        static GUI& getGUI();
        void init();
        void newFrame();
        void render();
        void addMessage(const std::string& newMessage);
        void freeResources();

        void setPhonExpSetting(float phongExp);
        void setDiffSetting(float x, float y, float z);
        void setAmbSetting(float x, float y, float z);
        void setSpecSetting(float x, float y, float z);

        void setLDiffSetting(float x, float y, float z);
        void setLAmbSetting(float x, float y, float z);
        void setLSpecSetting(float x, float y, float z);
        void setGamma(float gamma);
        void setAttenuation(float s);

        void setColorPickerWindowPos(float&& x, float&& y);
        void setMessagesWindowPos(float&& x, float&& y);
        void setShaderLoaderWindowPos(float&& x, float&& y);
        void setCameraWindowPos(float&& x, float&& y);
        void setModelMoveSetWindowPos(float&& x, float&& y);
        void setFileExplorerWindowPos(float&& x, float&& y);
        void setRendererPropertiesWindowPos(float&& x, float&& y);
        void setLightingWindowPos(float&& x, float&& y);

        void setColorPickerWindowSize(float&& w, float&& h);
        void setMessagesWindowSize(float&& w, float&& h);
        void setShaderLoaderWindowSize(float&& w, float&& h);
        void setCameraWindowSize(float&& w, float&& h);
        void setModelMoveSetWindowSize(float&& w, float&& h);
        void setFileExplorerWindowSize(float&& w, float&& h);
        void setRendererPropertiesWindowSize(float&& w, float&& h);
        void setLightingWindowSize(float&& w, float&& h);

        void createWindows();
        bool captureMouse();

        float getPhongExpSetting() const;
        const float* getDiffSetting() const;
        const float* getAmbSetting() const;
        const float* getSpecSetting() const;

        const float* getLDiffSetting() const;
        const float* getLAmbSetting() const;
        const float* getLSpecSetting() const;
        float getGamma() const;
        float getAttenuation() const;

        ImVec4 getColor() const;
        void setColor(float x, float y, float z, float w);

        const std::string& getShaderName();
        bool getShaderButtonState() const;
        void setShaderButtonState(bool buttonState);

        CameraMove getCameraSelectedMove() const;
        CameraMoveDirection getCameraMoveDirection() const;
        bool getCameraPerspProjection() const;
        void setZoom(float zoom);
        float getZoom() const;
        void resetCameraButtons();
        void resetModelButtons();

        ModelMove getModelMove() const;
        ModelMoveDirection getModelMoveDirection() const;
        int getSelectedModel() const;
        int getNumberModels() const;
        void setSelectedModel(int selectedModel);
        bool destroyModel() const;
        void setNumberModels(int numberModels);
        void resetDestroySelectedModelButton();

        bool ObjFileHasBeenSelected() const;
        std::string getSelectedObjFile();
        void clearSelectedObjFile();

        bool getTriangleMesh() const;

        int getSelectedLight() const;
        int getNumberLights() const;
        void setSelectedLight(int selectedLight);
        void setNumberLights(int numberLights);
    };
} // PAG

#endif //PAG_PROJECT_GUI_H
