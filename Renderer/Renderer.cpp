//
// Created by ahues on 20/09/2024.
//

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include "Renderer.h"

namespace PAG {
    Renderer* Renderer::_singleton = nullptr;

    Renderer& Renderer::getRenderer() {
        if(!_singleton)
            _singleton = new Renderer();
        return *_singleton;
    }

    Renderer::Renderer() {
        _clearColor = glm::vec4(0.6, 0.6, 0.6, 1.0);
        _triangleShaderProgram = new ShaderProgram;
        _camera = new Camera;
    }

    Renderer::~Renderer() {
        delete _triangleShaderProgram;
        _triangleShaderProgram = nullptr;
        delete _camera;
        _camera = nullptr;
    }

    void Renderer::init() {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_MULTISAMPLE);
    }

    void Renderer::setClearColor(glm::vec4& newColor) {
        this->_clearColor = newColor;
    }

    void Renderer::setClearColor(float R, float G, float B, float A) {
        this->_clearColor = glm::vec4(R,G,B,A);
    }

    glm::vec4 Renderer::getClearColor() {
        return this->_clearColor;
    }

    void Renderer::creaTriangulo() {
        Model model;

        model.setVertexAttributtes(std::vector<vertex>({ vertex{glm::vec3(-.5, -.5, 0),glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0)},
                                                                             vertex{glm::vec3(.5, -.5, 0),glm::vec3(0.0, 1.0,0.0), glm::vec3(0.0, 0.0, 0.0)},
                                                                             vertex{glm::vec3(.0, .5, 0),glm::vec3(0.0, 0.0,1.0), glm::vec3(0.0, 0.0, 0.0)}}));
        model.setIndexes({0, 1, 2});
        _models.emplace_back(std::move(model));
        _models.back().createModel();
        _selectedModel = 0;
    }

    void Renderer::crearModelo(const std::string& path) {


        _selectedModel = _models.size() - 1;
    }

    void Renderer::destruirModeloSeleccionado() {
        _models.erase(_models.begin() + _selectedModel);
        _selectedModel = -1;
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (_triangleShaderProgram->createdSuccessfully()) {
            _triangleShaderProgram->use();
            _triangleShaderProgram->setUniform("projection", _camera->getProjection());
            _triangleShaderProgram->setUniform("view", _camera->getVision());
            for(Model& model : _models) {
                model.setShaderProgram(_triangleShaderProgram);
                model.render();
            }
        }
    }

    void Renderer::cursorPos(double xPos, double yPos, float deltaTime) {
        static double xOldPos = 0.0;
        static double yOldPos = 0.0;

        if(_cameraCursorMovementAllowed) {
            int yDir;
            int xDir;

            if(glm::epsilonEqual(yPos, yOldPos, glm::epsilon<double>()))
                yDir = 0;
            else
                yDir = (yPos - yOldPos) > 0 ? -1 : 1;

            if(glm::epsilonEqual(xPos, xOldPos, glm::epsilon<double>()))
                xDir = 0;
            else
                xDir = (xPos - xOldPos) < 0 ? -1 : 1;

            switch(_cameraMovement) {
                case CameraMove::CRANE:
                    _camera->crane(yDir * CRANE_DEFAULT_SPEED * deltaTime);
                    break;
                case CameraMove::DOLLY:
                    _camera->dolly(xDir * DOLLY_DEFAULT_SPEED * deltaTime, -yDir * DOLLY_DEFAULT_SPEED * deltaTime);
                    break;
                case CameraMove::TILT:
                    _camera->tilt(yDir * TILT_DEFAULT_SPEED * deltaTime);
                    break;
                case CameraMove::PAN:
                    _camera->pan(-xDir * PAN_DEFAULT_SPEED * deltaTime);
                    break;
                case CameraMove::ORBIT:
                    _camera->orbit(xDir * ORBIT_DEFAULT_SPEED * deltaTime, -yDir * ORBIT_DEFAULT_SPEED * deltaTime);
                    break;
                case CameraMove::ZOOM:
                    _camera->zoom(xDir * ZOOM_DEFAULT_SPEED * deltaTime);
                    break;
            }
        }

        xOldPos = xPos;
        yOldPos = yPos;
    }

    int Renderer::getSelectedModel() const { return _selectedModel; }
    void Renderer::setSelectedModel(int selected) { _selectedModel = selected; }
    int Renderer::getNumberModels() const { return _models.size(); }

    void Renderer::setModelMoveDir(ModelMoveDirection direction) {
        if(_selectedModel < 0)
            return;

        int moveType1 = 0, moveType2 = 0, moveType3 = 0;

        switch(direction) {
            case ModelMoveDirection::move1:
                moveType1 = 1;
                break;
            case ModelMoveDirection::move2:
                moveType1 = -1;
                break;
            case ModelMoveDirection::move3:
                moveType2 = 1;
                break;
            case ModelMoveDirection::move4:
                moveType2 = -1;
                break;
            case ModelMoveDirection::move5:
                moveType3 = 1;
                break;
            case ModelMoveDirection::move6:
                moveType3 = -1;
                break;
            case ModelMoveDirection::resetModDir:
                return;
        }

        switch(_modelMovement) {
            case ModelMove::translation:
                _models[_selectedModel].translateModel(glm::vec3(moveType1, moveType2, moveType3));
                break;
            case ModelMove::rotation:
                _models[_selectedModel].rotateModel(5.0f, glm::vec3(moveType1, moveType2, moveType3));
                break;
            case ModelMove::scale:
                _models[_selectedModel].scaleModel(0.05f * glm::vec3(moveType1, moveType2, moveType3));
                break;
        }
    }

    void Renderer::setCameraMoveDir(CameraMoveDirection direction) {
        int up = 0, down = 0, left = 0, right = 0;

        switch(direction) {
            case CameraMoveDirection::uMove:
                up = 1;
                break;
            case CameraMoveDirection::rMove:
                right = 1;
                break;
            case CameraMoveDirection::lMove:
                left = -1;
                break;
            case CameraMoveDirection::dMove:
                down = -1;
                break;
            case CameraMoveDirection::resetCamDir:
                return;
        }

        switch(_cameraMovement) {
            case CameraMove::CRANE:
                _camera->crane(static_cast<float>(up + down) * 0.1f);
                break;
            case CameraMove::DOLLY:
                _camera->dolly(static_cast<float>(left + right) * 0.1f, -static_cast<float>(up + down) * 0.1f);
                break;
            case CameraMove::TILT:
                _camera->tilt(static_cast<float>(up + down) * 1.0f);
                break;
            case CameraMove::PAN:
                _camera->pan(-static_cast<float>(left + right) * 1.0f);
                break;
            case CameraMove::ORBIT:
                _camera->orbit(static_cast<float>(left + right) * 3.0f, -static_cast<float>(up + down) * 3.0f);
                break;
        }
    }

    void Renderer::ratonRueda(double xoffset, double yoffset) {
        //yoffset es 0 si la rueda del raton no esta en movimiento, -1 cuando gira hacia abajo, 1 hacia arriba
        float slope = 0.015f;

        if (yoffset < 0){
            float min = _clearColor[0];
            for(int i = 0; i < glm::vec4::length() - 1; i++) {
                _clearColor[i] -= slope;
                if(min > _clearColor[i])
                    min = _clearColor[i];
            }

            if(min < 0)
                for(int i = 0; i < glm::vec4::length() - 1; i++)
                    if(_clearColor[i] < 0)
                        _clearColor[i] -= min;

        }else if(yoffset > 0) {
            float max = -1;
            for(int i = 0; i < glm::vec4::length() - 1; i++) {
                _clearColor[i] += slope;
                if(max < _clearColor[i])
                    max = _clearColor[i];
            }

            if(max > 1)
                for(int i = 0; i < glm::vec4::length() - 1; i++)
                    _clearColor[i] /= max;

        }
    }

    void Renderer::tamanoViewport(int width, int height) {
        glViewport(0, 0, width, height);

        _camera->setScope(static_cast<float>(width), static_cast<float>(height));
    }

    ShaderProgram& Renderer::getShaderProgram() { return *_triangleShaderProgram; }

    Camera& Renderer::getCamera() { return *_camera; }

    const std::string Renderer::getInforme() {
        std::string resultado;

        resultado.append((const char*)glGetString(GL_RENDERER));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_VENDOR));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_VERSION));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

        return resultado;
    }

    void Renderer::setCameraCursorMovementAllowed(bool allowed) { _cameraCursorMovementAllowed = allowed; }

    void Renderer::setCameraMove(CameraMove move) { _cameraMovement = move; }

    void Renderer::setModelMove(ModelMove move) { _modelMovement = move; }

    void Renderer::setCameraPerspProjection(bool perspProjection) { _camera->setProjectionType(perspProjection); }
} // PAG