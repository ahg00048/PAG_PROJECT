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
#include "../Light/Light.h"

#define N_LIGHTS 4

#define POINT_LIGHT_POS 0
#define SPOTLIGHT_POS 1
#define DIRECTIONAL_LIGHT_POS 2
#define AMBIENT_LIGHT_POS 3

namespace PAG {
    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;

        //models
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

        //lights
        int _selectedLight = -1;
        std::array<Light, 4> _lights;

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

        void setCurrentLightDiff(const float* diff);
        void setCurrentLightAmb(const float* amb);
        void setCurrentLightSpec(const float* spec);
        void setCurrentLightGamma(float gamma);
        void setCurrentLightAttenuation(float s);

        glm::vec4 getClearColor();
        //modelos
        void creaTriangulo();
        void crearModelo(const std::string& path);
        void destruirModeloSeleccionado();

        const glm::vec3& getCurrentModelDiff();
        const glm::vec3& getCurrentModelAmb();
        const glm::vec3& getCurrentModelSpec();
        float getCurrentModelPhongExp();

        const glm::vec3& getCurrentLightDiff();
        const glm::vec3& getCurrentLightAmb();
        const glm::vec3& getCurrentLightSpec();
        float getCurrentLightGamma();
        float getCurrentLightAttenuation();

        int getSelectedLight() const;
        bool setSelectedLight(int selected);

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
