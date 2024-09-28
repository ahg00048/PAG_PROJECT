//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <glad/glad.h>

namespace PAG {
    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;

        GLuint idVS = 0; // Identificador del vertex shader
        GLuint idFS = 0; // Identificador del fragment shader
        GLuint idSP = 0; // Identificador del shader program
        GLuint idVAO = 0; // Identificador del vertex array object
        GLuint idVBO = 0; // Identificador del vertex buffer object
        GLuint idIBO = 0; // Identificador del index buffer object

        //shaders
        bool _shaderFailure = false;
        std::string _vsContent = "";
        std::string _fsContent = "";

        Renderer();
    public:
        virtual ~Renderer();
        static Renderer& getRenderer();
        void init();
        //color de fondo
        void setClearColor(glm::vec4& newColor);
        void setClearColor(float R, float G, float B, float A);
        glm::vec4 getClearColor();
        //Shaders
        void creaShaderProgram();
        void obtenerShaders(const std::string& path);
        //modelos
        void creaModelo();
        void refrescar();
        void ratonRueda(double xoffset, double yoffset);
        void tamanoViewport(int width, int height);
        std::string getInforme();
    };
} // PAG

#endif //PAG_PROJECT_RENDERER_H
