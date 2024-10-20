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

    //TODO
    void ShaderProgram::deleteShaderProgram() {
        if(_id == 0)
            return;

        std::vector<GLuint> attachedShaders = getAttachedShaders();
        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            if(std::find(attachedShaders.begin(), attachedShaders.end(), it->second.getId()) != attachedShaders.end()) {
                it->second.deleteShader();
                glDetachShader(_id, it->second.getId());
            }
            it++;
        }
        glDeleteProgram(_id);
    }

    GLuint ShaderProgram::getId() const {
        return _id;
    }

    std::vector<GLuint> ShaderProgram::getAttachedShaders() {
        std::vector<GLuint> attachedShaders(_shaders.size());
        GLsizei count = 0;
        GLuint* attachedShadersPtr = nullptr;
        glGetAttachedShaders(_id, static_cast<GLsizei>(_shaders.size()), &count, attachedShadersPtr);

        for(int i = 0; i < count; i++)
            attachedShaders.emplace_back(attachedShadersPtr[i]);

        return attachedShaders;
    }

    void ShaderProgram::createShaderProgram() {
        _id = glCreateProgram();
        if(_id == 0)
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del programa de shaders");

        std::vector<GLuint> attachedShaders = getAttachedShaders();
        auto it = _shaders.begin();
        while(it != _shaders.end()) {
            it->second.compile();
            if(std::find(attachedShaders.begin(), attachedShaders.end(), it->second.getId()) == attachedShaders.end())
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

    bool ShaderProgram::created() const {
        return 0 != _id;
    }

    void ShaderProgram::detachShader(GLuint shader) {
        auto it = _shaders.begin();
        while(it != _shaders.end())
            if(it->second.getId() == shader)
                ;
    }
} // PAG