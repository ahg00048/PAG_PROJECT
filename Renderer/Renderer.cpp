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

    }

    Renderer::~Renderer() {

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
        float colors[4];
        glGetFloatv(GL_COLOR_CLEAR_VALUE, colors);

        float slope = 0.015;

        if (yoffset < 0){
            float min = colors[0];
            for(float& color : colors) {
                color -= slope;
                if(min > color)
                    min = color;
            }

            if(min < 0)
                for(float& color : colors)
                    color *= -min;

        }else if(yoffset > 0) {
            float max = -1;
            for(float& color : colors) {
                color += slope;
                if(max < color)
                    max = color;
            }

            if(max > 1)
                for(float& color : colors)
                    color /= max;

        }
        glClearColor(colors[0],colors[1],colors[2],1);
    }

    void Renderer::tamanoViewport(int width, int height) {
        glViewport(0, 0, width, height);
    }
} // PAG