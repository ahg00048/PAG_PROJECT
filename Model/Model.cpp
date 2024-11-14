//
// Created by ahues on 02/11/2024.
//

#include "Model.h"

namespace PAG {
    Model::Model(): _idIBO(0), _idVBO(0), _idVAO(0),
                    _transformMatrix(glm::identity<glm::mat4>()) {

    }

    Model::Model(const Model& orig): _idIBO(orig._idIBO), _idVBO(orig._idVBO), _idVAO(orig._idVAO),
                                     _transformMatrix(orig._transformMatrix), _indexes(orig._indexes),
                                     _vertexAtributtes(orig._vertexAtributtes) {

    }

    Model::Model(const std::vector<vertex>& vertexAtributtes, const std::vector<unsigned int>& indexes):
        _vertexAtributtes(vertexAtributtes), _indexes(indexes),
        _idIBO(0), _idVBO(0), _idVAO(0),
        _transformMatrix(glm::identity<glm::mat4>()) {

    }

    Model::~Model() {

    }

    void Model::createModel() {
        // Generamos el VAO
        glGenVertexArrays(1, &_idVAO);
        glBindVertexArray(_idVAO);

        // VBO ENTRELAZADO
        glGenBuffers(1, &_idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _idVBO);

        glBufferData(GL_ARRAY_BUFFER, _vertexAtributtes.size() * sizeof(vertex), _vertexAtributtes.data(), GL_STATIC_DRAW);

        //posiciones
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);
        glEnableVertexAttribArray(0);
        //colores
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, color)));
        glEnableVertexAttribArray(1);
        //normales
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<void*>(offsetof(vertex, normal)));
        glEnableVertexAttribArray(2);

        // Generamos el IBO
        glGenBuffers(1, &_idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(GLuint), _indexes.data(), GL_STATIC_DRAW);
    }

    void Model::destroyModel() {
        if(_idVBO != 0)
            glDeleteBuffers(1, &_idVBO);
        if(_idIBO != 0)
            glDeleteBuffers(1, &_idIBO);
        if(_idVAO != 0)
            glDeleteVertexArrays(1, &_idVAO);
    }

    void Model::render() {
        glBindVertexArray(_idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
        glDrawElements(GL_TRIANGLES, _indexes.size(), GL_UNSIGNED_INT, nullptr);
    }

    void Model::setVertexAttributtes(const std::vector<vertex>& vertexAtributtes) { _vertexAtributtes = vertexAtributtes; }
    void Model::setIndexes(const std::vector<unsigned int>& indexes) { _indexes = indexes; }

    void Model::setMaterial(const PAG::Material &material) { _material = material; }

    void Model::setModelPos(const glm::vec3& position) { _transformMatrix = glm::translate(position); }

    void Model::translateModel(const glm::vec3& translation) { _transformMatrix = glm::translate(translation) * _transformMatrix; }
    void Model::rotateModel(float angle, const glm::vec3& axis) { _transformMatrix *= glm::rotate(glm::radians(angle), axis); }
    void Model::scaleModel(const glm::vec3& scale) { _transformMatrix *= glm::scale(scale); }

    const glm::mat4& Model::getModelMatrix() const { return _transformMatrix; }

    const Material& Model::getMaterial() const { return _material; }
} // PAG