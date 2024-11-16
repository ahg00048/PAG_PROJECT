//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../ShaderProgram/ShaderProgram.h"
#include "../GUI/GUI.h"
#include "../Camara/Camera.h"
#include "../Model/Model.h"

namespace PAG {
    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;

        std::vector<Model> _models;
        int _selectedModel = -1;
        ModelMove _modelMovement;

        //shaders
        ShaderProgram* _shaderProgram = nullptr;

        //Camara
        Camera* _camera = nullptr;
        CameraMove _cameraMovement;
        bool _cameraCursorMovementAllowed = false;
        bool _triangleMesh = false;

        void processNode(aiNode* node, const aiScene *scene);
        void processMesh(aiMesh* mesh);

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
        void setModelMove(ModelMove move);
        void setModelMoveDir(ModelMoveDirection direction);
        void setTriangleMesh(bool triangleMesh);
        void setCurrentModelDiff(const float* diff);
        void setCurrentModelAmb(const float* amb);
        void setCurrentModelSpec(const float* spec);
        void setCurrentModelPhongEXP(float phongExp);

        glm::vec4 getClearColor();
        //modelos
        void creaTriangulo();
        void crearModelo(const std::string& path);
        void destruirModeloSeleccionado();

        const glm::vec3& getCurrentModelDiff();
        const glm::vec3& getCurrentModelAmb();
        const glm::vec3& getCurrentModelSpec();
        float getCurrentModelPhongExp();

        int getSelectedModel() const;
        bool setSelectedModel(int selected);
        int getNumberModels() const;

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
