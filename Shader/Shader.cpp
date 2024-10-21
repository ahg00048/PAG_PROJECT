//
// Created by ahues on 04/10/2024.
//

#include <fstream>
#include <sstream>

#include "Shader.h"

namespace PAG {
    Shader::Shader():
        _id(0), _content(), _type(undefined) {

    }

    Shader::Shader(ShaderType type):
            _id(0), _content(), _type(type) {
    }

    Shader::Shader(ShaderType type, const std::string& path):
        _id(0), _content(), _type(type) {
        setContentFromFile(path);
    }

    Shader::Shader(const Shader& orig):
        _id(orig._id), _content(orig._content), _type(orig._type) {

    }

    Shader::~Shader() {
        if(_id != 0)
            glDeleteShader(_id);
    }

    GLuint Shader::getId() const {
        return _id;
    }

    void Shader::setType(const PAG::ShaderType type) {
        _type = type;
    }

    ShaderType Shader::getType() const {
        return _type;
    }

    void Shader::setContent(const std::string& content) {
        _content = content;
    }

    bool Shader::empty() const {
        return _content.empty();
    }

    bool Shader::compiledSuccessfully() const {
        return _id != 0;
    }

    void Shader::setContentFromFile(const std::string& path) {
        std::ifstream shaderFile;
        std::stringstream shaderStream;

        shaderFile.open(path);
        if(!shaderFile.is_open()) { // Error abriendo el archivo
            deleteShader();
            throw std::runtime_error("[PAG::Shader::obtainContent]: Error en la apertura del archivo");
        }
        shaderStream << shaderFile.rdbuf();
        _content = shaderStream.str();

        shaderFile.close();
    }

    void Shader::compile() {
        if(_type == undefined) {
            deleteShader();
            throw std::runtime_error("[PAG::Shader::compile]: Error shader of undefined tyoe");
        }

        _id = glCreateShader(_type);

        if(_id == 0) {
            deleteShader();
            throw std::runtime_error("[PAG::Shader::compile]: Error en la creación del vertex shader");
        }

        const GLchar* shaderSource = _content.c_str();
        glShaderSource(_id, 1, &shaderSource, nullptr);
        glCompileShader(_id);

        //comprobamos que la compilacion del shader no ha sido un exito
        GLint CompilationSuccess;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &CompilationSuccess);

        if(CompilationSuccess == GL_FALSE) {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el message de error de OpenGL
            GLint msgSize = 0;
            std::string message = "";
            glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &msgSize);
            // Comprobamos que el message no sea nulo
            if(msgSize > 0) {
                GLchar* buffer = new GLchar[msgSize];
                GLint bufferSize = 0;
                glGetShaderInfoLog(_id, msgSize, &bufferSize, buffer);
                message.assign(buffer);
                delete[] buffer;
                buffer = nullptr;
            }
            deleteShader();
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (shader compilation)\n  " + message);
        }
    }

    void Shader::deleteShader() {
        _content.clear();
        if(_id != 0)
            glDeleteShader(_id);

        _id = 0;
    }
} // PAG