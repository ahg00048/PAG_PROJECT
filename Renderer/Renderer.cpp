//
// Created by ahues on 20/09/2024.
//

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include "Renderer.h"

#define ENTRELAZADO true

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
#if ENTRELAZADO
        if(idVBO != 0)
            glDeleteBuffers(1, &idVBO);
#else
        for(int i = 0; i < 2; i++)
            if(_idVBOs[i] != 0)
                glDeleteBuffers(1, &_idVBOs[i]);
#endif
        if(idIBO != 0)
            glDeleteBuffers(1, &idIBO);
        if(idVAO != 0)
            glDeleteVertexArrays(1, &idVAO);
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

    void Renderer::creaModelo() {
        // Geometria
#if ENTRELAZADO
        //con un solo VBO entrelazado
        GLfloat verticesAndColors[] = {-.5, -.5, 0,     1.0, 0.0, 0.0,
                                        .5, -.5, 0,      0.0, 1.0,0.0,
                                        .0, .5, 0,    0.0, 0.0,1.0};
#else
        //con dos VBO no entrelazados
        GLfloat vertices[] = {-.5, -.5, 0,
                               .5, -.5, 0,
                               .0, .5, 0};

        GLfloat colors[] = {1.0, 0.0, 0.0,
                            0.0, 1.0,0.0,
                            0.0, 0.0,1.0};
#endif
        // Topologia
        GLuint indices[] = {0, 1, 2};

        // Generamos el VAO
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        // Generamos el VBO
#if ENTRELAZADO
        // VBO ENTRELAZADO
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);

        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticesAndColors, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
#else
        // VBOS NO ENTRELAZADOS
        glGenBuffers(2, _idVBOs);
        glBindBuffer(GL_ARRAY_BUFFER,  _idVBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,  _idVBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(1);
#endif
        // Generamos el IBO
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (_triangleShaderProgram->createdSuccessfully()) {
            glBindVertexArray(idVAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
            _triangleShaderProgram->use();
            _triangleShaderProgram->setUniform("projection", _camera->getProjection());
            _triangleShaderProgram->setUniform("view", _camera->getVision());
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::cursorPos(double xPos, double yPos, float deltaTime) {
        static double xOldPos = 0.0;
        static double yOldPos = 0.0;

        if(_cameraMovementAllowed) {
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

        _camera->setScope(static_cast<float>(width) / static_cast<float>(height));
    }

    ShaderProgram& Renderer::getShaderProgram() {
        return *_triangleShaderProgram;
    }

    Camera& Renderer::getCamera() {
        return *_camera;
    }

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

    void Renderer::setCameraMovementAllowed(bool allowed) {
        _cameraMovementAllowed = allowed;
    }

    void Renderer::setCameraMove(CameraMove move) {
        _cameraMovement = move;
    }

    void Renderer::setCameraPerspProjection(bool perspProjection) {
        _camera->setProjType(perspProjection);
    }
} // PAG