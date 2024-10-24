//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <glad/glad.h>

#include "../ShaderProgram/ShaderProgram.h"
#include "../GUI/GUI.h"
#include "../Camara/Camera.h"

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
        ShaderProgram* _triangleShaderProgram = nullptr;

        //Camara
        Camera* _camera = nullptr;
        CameraMove _cameraMovement;
        bool _cameraCursorMovementAllowed = false;

        Renderer();
    public:
        virtual ~Renderer();
        static Renderer& getRenderer();
        void init();
        //color de fondo
        void setClearColor(glm::vec4& newColor);
        void setClearColor(float R, float G, float B, float A);
        void setCameraCursorMovementAllowed(bool allowed);
        void setCameraMove(CameraMove move);
        void setCameraPerspProjection(bool perspProjection);
        void setCameraMoveDir(CameraMoveDirection direction);

        glm::vec4 getClearColor();
        //modelos
        void creaModelo();

        void cursorPos(double xPos, double yPos, float deltaTime);
        void refrescar();
        void ratonRueda(double xoffset, double yoffset);
        void tamanoViewport(int width, int height);
        const std::string getInforme();
        //shader
        ShaderProgram& getShaderProgram();
        Camera& getCamera();
    };
} // PAG

#endif //PAG_PROJECT_RENDERER_H
