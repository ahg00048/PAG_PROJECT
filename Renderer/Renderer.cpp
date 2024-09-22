//
// Created by ahues on 20/09/2024.
//

#include <string>

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
    }

    Renderer::~Renderer() {

    }

    void Renderer::init() {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
        glEnable (GL_DEPTH_TEST);
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

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ratonRueda(double xoffset, double yoffset) {
        //yoffset es 0 si la rueda del raton no esta en movimiento, -1 cuando gira hacia abajo, 1 hacia arriba
        float slope = 0.03;

        if (yoffset < 0){
            float min = _clearColor[0];
            for(int i = 0; i < glm::vec4::length(); i++) {
                _clearColor[i] -= slope;
                if(min > _clearColor[i])
                    min = _clearColor[i];
            }

            if(min < 0)
                for(int i = 0; i < glm::vec4::length(); i++)
                    _clearColor[i] -= min;

        }else if(yoffset > 0) {
            float max = -1;
            for(int i = 0; i < glm::vec4::length(); i++) {
                _clearColor[i] += slope;
                if(max < _clearColor[i])
                    max = _clearColor[i];
            }

            if(max > 1)
                for(int i = 0; i < glm::vec4::length(); i++)
                    _clearColor[i] /= max;

        }
    }

    void Renderer::render() {
        glClearColor(_clearColor[0],_clearColor[1], _clearColor[2],_clearColor[3]);
    }

    void Renderer::tamanoViewport(int width, int height) {
        glViewport(0, 0, width, height);
    }
} // PAG