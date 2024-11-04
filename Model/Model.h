//
// Created by ahues on 02/11/2024.
//

#ifndef PAG_PROJECT_MODEL_H
#define PAG_PROJECT_MODEL_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "../ShaderProgram/ShaderProgram.h"

namespace PAG {
    struct vertex {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal;
    };

    class Model {
    private:
        GLuint _idIBO;
        GLuint _idVAO;
        GLuint _idVBO;

        std::vector<vertex> _vertexAtributtes;
        std::vector<int> _indexes;

        glm::mat4 _transformMatrix;
  
        ShaderProgram* _shaderProgram;
    public:
        Model();
        Model(const Model& orig);
        ~Model();

        void setVertexAttributtes(const std::vector<vertex>& vertexAtributtes);
        void setIndexes(const std::vector<int>& indexes);
        void createModel();
        void destroyModel();
        void render();

        void setShaderProgram(ShaderProgram* shaderProgram);

        void translateModel(const glm::vec3& translation);
        void rotateModel(const float angle, const glm::vec3& axis);
        void scaleModel(const glm::vec3& scale);

        void setModelPos(const glm::vec3& position);

        const glm::mat4& getModelMatrix() const;
    };
} // PAG

#endif //PAG_PROJECT_MODEL_H
