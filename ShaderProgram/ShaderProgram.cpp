//
// Created by ahues on 19/10/2024.
//

#include "ShaderProgram.h"

#include <stdexcept>

namespace PAG {
    ShaderProgram::ShaderProgram():
        _id(0), _shaders() {

    }

    ShaderProgram::ShaderProgram(const ShaderProgram& orig):
        _id(orig._id), _shaders(orig._shaders) {

    }

    ShaderProgram::~ShaderProgram() {
        deleteShaderProgram();
    }

    void ShaderProgram::deleteShaderProgram() {
        detachShaders();

        glDeleteProgram(_id);
        _id = 0;
    }

    GLuint ShaderProgram::getId() const {
        return _id;
    }

    std::vector<GLuint> ShaderProgram::getAttachedShaders() {
        std::vector<GLuint> attachedShaders(_shaders.size());

        GLsizei count = 0;
        if(_id != 0)
            glGetAttachedShaders(_id, static_cast<GLsizei>(_shaders.size()), &count, attachedShaders.data());
        attachedShaders.resize(count);

        return attachedShaders;
    }

    void ShaderProgram::createShaderProgram() {
        glDeleteProgram(_id);

        _id = glCreateProgram();
        if(_id == 0)
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error at shaderProgram creation");

        std::vector<GLuint> attachedShaders = getAttachedShaders();
        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            if(!it->second->compiledSuccessfully())
                throw std::runtime_error("[PAG::Renderer::createShaderProgram]: Error, shaders must be compiled before attaching them to a shader program");
            if(std::find(attachedShaders.begin(), attachedShaders.end(), it->second->getId()) == attachedShaders.end())
                glAttachShader(_id, it->second->getId());
            it++;
        }

        glLinkProgram(_id);

        GLint linkSuccess = 0;
        glGetProgramiv(_id, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE) {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(_id, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (Program link)\n  " + mensaje);
        }
    }

    void ShaderProgram::addShader(std::shared_ptr<Shader>& shader) {
        _shaders.emplace(shader->getType(), shader.get());
    }

    void ShaderProgram::removeShader(ShaderType type) {
        _shaders.erase(type);
    }

    std::vector<std::shared_ptr<Shader>> ShaderProgram::getEmptyShaders() {
        std::vector<std::shared_ptr<Shader>> emptyShaders;

        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            if(it->second->empty())
                emptyShaders.emplace_back(it->second);
            it++;
        }

        return emptyShaders;
    }

    std::vector<std::shared_ptr<Shader>> ShaderProgram::getShaders() {
        std::vector<std::shared_ptr<Shader>> shaders;

        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            shaders.emplace_back(it->second);
            it++;
        }

        return shaders;
    }

    bool ShaderProgram::createdSuccessfully() const {
        return 0 != _id;
    }

    void ShaderProgram::detachShader(GLuint shaderId) {
        std::vector<GLuint> attachedShaders = getAttachedShaders();
        for(GLuint attachedShader : attachedShaders) {
            if(shaderId == attachedShader) {
                glDetachShader(_id, shaderId);
                break;
            }
        }
    }

    std::shared_ptr<Shader> ShaderProgram::getShader(ShaderType type) {
        auto it = _shaders.find(type);
        return (it == _shaders.end()) ? std::shared_ptr<Shader>() : it->second;
    }

    std::shared_ptr<Shader> ShaderProgram::getShader(GLuint shaderId) {
        for(auto& shader : _shaders)
            if(shader.second->getId() == shaderId)
                return shader.second;

        return std::shared_ptr<Shader>();
    }

    void ShaderProgram::compileShaders() {
        for(auto& shader : _shaders) {
            if(shader.second->getType() != ShaderType::undefined && !shader.second->compiledSuccessfully())
                shader.second->compile();
        }
    }


    void ShaderProgram::detachShaders() {
        std::vector<GLuint> attachedShaders = getAttachedShaders();
        for(GLuint shader : attachedShaders)
            glDetachShader(_id, shader);
    }

    void ShaderProgram::setUniform(const std::string& var, const glm::vec2& vec2) {
        int location = -1;
        if(_id != 0)
            location = glGetUniformLocation(_id, var.c_str());
        glUniform2f(location, vec2.x, vec2.y);
    }

    void ShaderProgram::setUniform(const std::string& var, const glm::vec3& vec3) {
        int location = -1;
        if(_id != 0)
            location = glGetUniformLocation(_id, var.c_str());
        glUniform3f(location, vec3.x, vec3.y, vec3.z);
    }

    void ShaderProgram::setUniform(const std::string& var, const glm::vec4& vec4) {
        int location = -1;
        if(_id != 0)
            location = glGetUniformLocation(_id, var.c_str());
        glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void ShaderProgram::setUniform(const std::string& var, const glm::mat3& mat3) {
        int location = -1;
        if(_id != 0)
            location = glGetUniformLocation(_id, var.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, &mat3[0][0]);
    }

    void ShaderProgram::setUniform(const std::string& var, const glm::mat4& mat4) {
        int location = -1;
        if(_id != 0)
            location = glGetUniformLocation(_id, var.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
    }

    void ShaderProgram::use() const {
        glUseProgram(_id);
    }
} // PAG