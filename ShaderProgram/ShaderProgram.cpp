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
        auto it = _shaders.begin();
        while (it != _shaders.end()) {
            glDetachShader(_id, it->second.getId());
            it++;
        }
        if(_id != 0)
            glDeleteProgram(_id);
    }

    GLuint ShaderProgram::getId() const {
        return _id;
    }

    bool ShaderProgram::shaderAttached(GLuint shader) {
        GLsizei count = 0;
        GLuint* attachedShaders = nullptr;
        glGetAttachedShaders(_id, _shaders.size(), &count, attachedShaders);

        for(int i = 0; i < count; i++)
            if(attachedShaders[i] == shader) {
                attachedShaders = nullptr;
                return true;
            }

        attachedShaders = nullptr;
        return false;
    }

    void ShaderProgram::createShaderProgram() {
        _id = glCreateProgram();
        if(_id == 0)
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del programa de shaders");

        GLint compilationSuccess;

        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            glGetShaderiv(it->second.getId(), GL_COMPILE_STATUS, &compilationSuccess);

            if(compilationSuccess == GL_FALSE)
                it->second.compile();

            if(!shaderAttached(it->second.getId()))
                glAttachShader(_id, it->second.getId());
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

    void ShaderProgram::addShader(Shader&& shader) {
        _shaders.emplace(shader.getType(), std::move(shader));
    }

    std::vector<Shader*> ShaderProgram::getEmptyShaders() {
        std::vector<Shader*> emptyShaders;

        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            if(it->second.empty())
                emptyShaders.emplace_back(&it->second);
            it++;
        }

        return emptyShaders;
    }

    std::vector<Shader*> ShaderProgram::getShaders() {
        std::vector<Shader*> shaders;

        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            shaders.emplace_back(&it->second);
            it++;
        }

        return shaders;
    }
} // PAG