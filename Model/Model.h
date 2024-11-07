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
        vertex() : position(), color(), normal() {}
        vertex(const glm::vec3& pos, const glm::vec3& col, const glm::vec3& norm) : position(pos), color(col), normal(norm) {}

        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal;
    };

    class Model {
    private:
        GLuint _idVAO;
        GLuint _idIBO;
        GLuint _idVBO;

        std::vector<vertex> _vertexAtributtes;
        std::vector<unsigned int> _indexes;

        glm::mat4 _transformMatrix;
    public:
        Model();
        Model(const std::vector<vertex>& vertexAtributtes, const std::vector<unsigned int>& indexes);
        Model(const Model& orig);
        ~Model();

        void setVertexAttributtes(const std::vector<vertex>& vertexAtributtes);
        void setIndexes(const std::vector<unsigned int>& indexes);
        void createModel();
        void destroyModel();
        void render();

        void translateModel(const glm::vec3& translation);
        void rotateModel(const float angle, const glm::vec3& axis);
        void scaleModel(const glm::vec3& scale);

        void setModelPos(const glm::vec3& position);

        const glm::mat4& getModelMatrix() const;
    };
} // PAG

#endif //PAG_PROJECT_MODEL_H
