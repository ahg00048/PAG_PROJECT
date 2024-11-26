//
// Created by ahues on 20/09/2024.
//

#include <fstream>
#include <stdexcept>

#include "Renderer.h"

#define MAX_N_ENTITIES 100

namespace PAG {
    Renderer* Renderer::_singleton = nullptr;

    Renderer& Renderer::getRenderer() {
        if(!_singleton)
            _singleton = new Renderer();
        return *_singleton;
    }

    Renderer::Renderer() {
        _clearColor = glm::vec4(0.6, 0.6, 0.6, 1.0);
        _shaderProgram = new ShaderProgram;
        _camera = new Camera;
        _models.reserve(MAX_N_ENTITIES);
        _lights[SPOTLIGHT_POS].setLightApplicator(LightApplicatorType::_spotLight);
        _lights[SPOTLIGHT_POS].setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
        _lights[SPOTLIGHT_POS].setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
        _lights[DIRECTIONAL_LIGHT_POS].setLightApplicator(LightApplicatorType::_directionalLight);
        _lights[DIRECTIONAL_LIGHT_POS].setDirection(glm::vec3(1.0f, 0.0f, 0.0f));
        _lights[POINT_LIGHT_POS].setLightApplicator(LightApplicatorType::_pointLight);
        _lights[POINT_LIGHT_POS].setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
        _lights[AMBIENT_LIGHT_POS].setLightApplicator(LightApplicatorType::_ambientLight);
    }
    Renderer::~Renderer() {
        delete _shaderProgram;
        _shaderProgram = nullptr;
        delete _camera;
        _camera = nullptr;

        for(Model& model : _models) {
            model.destroyModel();
            delete model.getMaterial();
            model.setMaterial(nullptr);
        }
        _models.clear();
    }

    void Renderer::init() {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
    }

    void Renderer::setClearColor(glm::vec4& newColor) { this->_clearColor = newColor; }
    void Renderer::setClearColor(float R, float G, float B, float A) { this->_clearColor = glm::vec4(R,G,B,A); }
    glm::vec4 Renderer::getClearColor() { return this->_clearColor; }

    void Renderer::creaTriangulo() {
        _models.emplace_back(std::vector<vertex>({ vertex{glm::vec3(-.5, -.5, 0),glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)},
                                                   vertex{glm::vec3(.5, -.5, 0),glm::vec3(0.0, 1.0,0.0), glm::vec3(0.0, 1.0, 0.0)},
                                                   vertex{glm::vec3(.0, .5, 0),glm::vec3(0.0, 0.0,1.0), glm::vec3(0.0, 1.0, 0.0)}}), std::vector<unsigned int>({0, 1, 2}));
        _models.back().createModel();
        _models.back().setMaterial(new Material);
        _selectedModel = 0;
    }
    void Renderer::crearModelo(const std::string& path) {
        if(path.empty())
            throw std::runtime_error("[Renderer::crearModelo]: Invalid path to .obj extension file");

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile (path,
                                                      aiProcess_JoinIdenticalVertices | aiProcess_Triangulate
                                                      | aiProcess_GenSmoothNormals);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            throw std::runtime_error(std::string("[Renderer::crearModelo]: ") + importer.GetErrorString());

        processNode(scene->mRootNode, scene);
    }

    void Renderer::processNode(aiNode *node, const aiScene *scene) {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh);
        }

        // then do the same for each of its children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
            processNode(node->mChildren[i], scene);
    }
    void Renderer::processMesh(aiMesh* mesh) {
        if (!mesh->mVertices)
            throw std::runtime_error( "[Renderer::processMesh]: the vertexes have not been processed properly");

        std::vector<vertex> vertexAttributes;
        std::vector<unsigned int> indexes;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            vertex meshVertex;
            // process vertex positions, normals and texture coordinates
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            meshVertex.position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            meshVertex.normal = vector;

            if(mesh->HasVertexColors(i)) {
                vector.x = mesh->mColors[i]->r;
                vector.y = mesh->mColors[i]->g;
                vector.z = mesh->mColors[i]->b;
                meshVertex.color = vector;
            }

            vertexAttributes.emplace_back(meshVertex);
        }

        if (!mesh->HasFaces())
            throw std::runtime_error( "[Renderer::processMesh]: the vertexes have are not related to any faces of the model");

        // process indices
        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indexes.push_back(face.mIndices[j]);
        }

        _models.emplace_back(vertexAttributes, indexes);
        _models.back().createModel();
        _models.back().setMaterial(new Material);
        _selectedModel++;
    }

    void Renderer::destruirModeloSeleccionado() {
        if(_selectedModel >= 0) {
            _models[_selectedModel].destroyModel();
            delete _models[_selectedModel].getMaterial();
            _models[_selectedModel].setMaterial(nullptr);
            _models.erase(_models.begin() + _selectedModel);
            _selectedModel--;
        }
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK,  (_triangleMesh) ? GL_LINE : GL_FILL);
        glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]);
        if (_shaderProgram->createdSuccessfully()) {
            _shaderProgram->use();
            (_triangleMesh) ? _shaderProgram->setUniformSubroutine("colorRed", ShaderType::fragmentShader) : _shaderProgram->setUniformSubroutine("colorDiff", ShaderType::fragmentShader);
            _shaderProgram->setUniform("projection", _camera->getProjection());
            _shaderProgram->setUniform("view", _camera->getVision());

            for(int i = 0; i < _lights.size(); i++) {
                glBlendFunc(GL_SRC_ALPHA, (i == 0) ? GL_ONE_MINUS_SRC_ALPHA : GL_ONE);

                _lights[i].setSubroutine(*_shaderProgram);
                _lights[i].setVision(_camera->getVision());
                _lights[i].applyLight(*_shaderProgram);

                for(Model &model: _models) {

                    _shaderProgram->setUniform("model", model.getModelMatrix());
                    _shaderProgram->setUniform("diffColor", model.getMaterial()->getDiffuse());
                    _shaderProgram->setUniform("Ka", model.getMaterial()->getAmbient());
                    _shaderProgram->setUniform("Ks", model.getMaterial()->getSpecular());
                    _shaderProgram->setUniform("Kd", model.getMaterial()->getDiffuse());
                    _shaderProgram->setUniform("shininess", model.getMaterial()->getPhongExp());
                    model.render();
                }
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
    bool Renderer::setSelectedModel(int selected) {
        bool diff = selected != _selectedModel;
        _selectedModel = selected;

        return diff;
    }
    int Renderer::getNumberModels() const { return (_shaderProgram->createdSuccessfully()) ? _models.size() : 0; }

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
                _models[_selectedModel].translateModel(glm::vec3(-moveType2, moveType1, moveType3));
                break;
            case ModelMove::rotation:
                _models[_selectedModel].rotateModel(5.0f, glm::vec3(moveType1, moveType2, moveType3));
                break;
            case ModelMove::scale:
                _models[_selectedModel].scaleModel(0.05f * glm::vec3(moveType1, moveType2, moveType3) + glm::vec3(1.0f));
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

    ShaderProgram& Renderer::getShaderProgram() { return *_shaderProgram; }
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
    void Renderer::setTriangleMesh(bool triangleMesh) { _triangleMesh = triangleMesh; }

    void Renderer::setCurrentModelDiff(const float* diff) {
        if(_selectedModel < 0 || _models.empty())
            return;

        _models[_selectedModel].getMaterial()->setDiffuse(glm::vec3(diff[0], diff[1], diff[2]));
    }
    void Renderer::setCurrentModelAmb(const float* amb) {
        if(_selectedModel < 0 || _models.empty())
            return;

        _models[_selectedModel].getMaterial()->setAmbient(glm::vec3(amb[0], amb[1], amb[2]));
    }
    void Renderer::setCurrentModelSpec(const float* spec) {
        if(_selectedModel < 0 || _models.empty())
            return;

        _models[_selectedModel].getMaterial()->setSpecular(glm::vec3(spec[0], spec[1], spec[2]));
    }
    void Renderer::setCurrentModelPhongEXP(float phongExp) {
        if(_selectedModel < 0 || _models.empty())
            return;

        _models[_selectedModel].getMaterial()->setPhongExp(phongExp);
    }

    const glm::vec3& Renderer::getCurrentModelDiff() {
        if(_selectedModel < 0 || _models.empty())
            return glm::vec3(0.0f);

        return _models[_selectedModel].getMaterial()->getDiffuse();
    }
    const glm::vec3& Renderer::getCurrentModelAmb() {
        if(_selectedModel < 0 || _models.empty())
            return glm::vec3(0.0f);

        return _models[_selectedModel].getMaterial()->getAmbient();
    }
    const glm::vec3& Renderer::getCurrentModelSpec() {
        if(_selectedModel < 0 || _models.empty())
            return glm::vec3(0.0f);

        return _models[_selectedModel].getMaterial()->getSpecular();
    }
    float Renderer::getCurrentModelPhongExp() {
        if(_selectedModel < 0 || _models.empty())
            return 0.0f;

        return _models[_selectedModel].getMaterial()->getPhongExp();
    }

    void Renderer::setCurrentLightDiff(const float* diff) {
        if(_selectedLight < 0)
            return;

        _lights[_selectedLight].setDI(glm::vec3(diff[0], diff[1], diff[2]));
    }
    void Renderer::setCurrentLightAmb(const float* amb) {
        if(_selectedLight < 0)
            return;

        _lights[_selectedLight].setAI(glm::vec3(amb[0], amb[1], amb[2]));
    }
    void Renderer::setCurrentLightSpec(const float* spec) {
        if(_selectedLight < 0)
            return;

        _lights[_selectedLight].setSI(glm::vec3(spec[0], spec[1], spec[2]));
    }
    void Renderer::setCurrentLightGamma(float gamma) {
        if(_selectedLight < 0)
            return;

        _lights[_selectedLight].setGamma(gamma);
    }
    void Renderer::setCurrentLightAttenuation(float s) {
        if(_selectedLight < 0)
            return;

        _lights[_selectedLight].setAttenuation(s);
    }

    const glm::vec3& Renderer::getCurrentLightDiff() {
        if(_selectedLight < 0)
            return glm::vec3(0.0f);

        _lights[_selectedLight].getDI();
    }
    const glm::vec3& Renderer::getCurrentLightAmb() {
        if(_selectedLight < 0)
            return glm::vec3(0.0f);

        _lights[_selectedLight].getAI();
    }
    const glm::vec3& Renderer::getCurrentLightSpec() {
        if(_selectedLight < 0)
            return glm::vec3(0.0f);

        _lights[_selectedLight].getSI();
    }
    float Renderer::getCurrentLightGamma() {
        if(_selectedLight < 0)
            return 0.0f;

        _lights[_selectedLight].getGamma();
    }
    float Renderer::getCurrentLightAttenuation() {
        if(_selectedLight < 0)
            return 0.0f;

        _lights[_selectedLight].getAttenuation();
    }

    int Renderer::getSelectedLight() const { return _selectedLight; }
    bool Renderer::setSelectedLight(int selected)  {
        bool diff = (selected != _selectedLight);
        _selectedLight = selected;

        return diff;
    }

} // PAG