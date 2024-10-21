//
// Created by ahues on 19/10/2024.
//

#ifndef PAG_PROJECT_SHADERPROGRAM_H
#define PAG_PROJECT_SHADERPROGRAM_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include <glm/matrix.hpp>
#include <glm/vector_relational.hpp>

#include "../Shader/Shader.h"

namespace PAG {
    class ShaderProgram {
    private:
        std::map<ShaderType, std::shared_ptr<Shader>> _shaders;
        GLuint _id;

        std::vector<GLuint> getAttachedShaders();
    public:
        ShaderProgram();
        ShaderProgram(const ShaderProgram& orig);
        ~ShaderProgram();

        GLuint getId() const;

        std::vector<std::shared_ptr<Shader>> getShaders();
        std::vector<std::shared_ptr<Shader>> getEmptyShaders();

        void createShaderProgram();

        void addShader(Shader* shader);
        void removeShader(ShaderType type);

        bool createdSuccessfully() const;
        void use() const;

        void deleteShaderProgram();
        void detachShader(GLuint shader);

        void setUniform(const std::string& var, const glm::vec2& vec2);
        void setUniform(const std::string& var, const glm::vec3& vec3);
        void setUniform(const std::string& var, const glm::vec4& vec4);
        void setUniform(const std::string& var, const glm::mat3& mat3);
        void setUniform(const std::string& var, const glm::mat4& mat4);
    };

} // PAG

#endif //PAG_PROJECT_SHADERPROGRAM_H
