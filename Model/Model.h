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
#include "../Material/Material.h"

namespace PAG {
    struct vertex {
        vertex(): position(), color(), normal() {}
        vertex(const glm::vec3& pos, const glm::vec3& col, const glm::vec3& norm) : position(pos), color(col), normal(norm) {}

        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec2 textCoord;
    };

    class Model {
    private:
        GLuint _idVAO;
        GLuint _idIBO;
        GLuint _idVBO;

        std::vector<vertex> _vertexAtributtes;
        std::vector<unsigned int> _indexes;

        glm::mat4 _transformMatrix;

        Material* _material;
    public:
        Model();
        Model(const std::vector<vertex>& vertexAtributtes, const std::vector<unsigned int>& indexes);
        Model(const Model& orig);
        ~Model();

        void setVertexAttributtes(const std::vector<vertex>& vertexAtributtes);
        void setIndexes(const std::vector<unsigned int>& indexes);
        void setMaterial(Material* material);

        const glm::mat4& getModelMatrix() const;
        Material* getMaterial();

        void createModel();
        void destroyModel();
        void render();

        void translateModel(const glm::vec3& translation);
        void scaleModel(const glm::vec3& scale);
        void rotateModel(float angle, const glm::vec3& axis);
    };
} // PAG

#endif //PAG_PROJECT_MODEL_H
