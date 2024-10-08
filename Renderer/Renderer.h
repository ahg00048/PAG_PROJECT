//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <glad/glad.h>

#include "../Shader/Shader.h"

namespace PAG {
    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;

        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object

        GLuint _idVBOs[2]; // Identificadores de los dos VBOs para los vertices y colores de forma individual

        //shaders
        Shader* _triangleShader = nullptr;

        Renderer();
    public:
        virtual ~Renderer();
        static Renderer& getRenderer();
        void init();
        //color de fondo
        void setClearColor(glm::vec4& newColor);
        void setClearColor(float R, float G, float B, float A);
        glm::vec4 getClearColor();
        //modelos
        void creaModelo();
        void refrescar();
        void ratonRueda(double xoffset, double yoffset);
        void tamanoViewport(int width, int height);
        std::string getInforme();
        //shader
        Shader& getShader();
    };
} // PAG

#endif //PAG_PROJECT_RENDERER_H
