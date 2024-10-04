//
// Created by ahues on 04/10/2024.
//

#include <fstream>
#include <sstream>

#include "Shader.h"

namespace PAG {
    Shader::Shader() {
        _shaderFailure = true;
    }

    Shader::~Shader() {
        if(_idVS != 0)
            glDeleteShader(_idVS);
        if(_idFS != 0)
            glDeleteShader(_idFS);
        if(_idSP != 0)
            glDeleteProgram(_idSP);
    }

    void Shader::cargarShaders(const std::string& path) {
        _shaderFailure = false;

        std::ifstream archivoShader;
        std::stringstream streamShader;

        archivoShader.open(path + "-vs.glsl");
        if(!archivoShader.is_open()) { // Error abriendo el archivo
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::obtenerShaders]: Error en la apertura del archivo");
        }
        streamShader << archivoShader.rdbuf();
        _vsContent = streamShader.str();

        archivoShader.close();

        streamShader.str(std::string());
        archivoShader.open(path + "-fs.glsl");
        if(!archivoShader.is_open()) {// Error abriendo el archivo
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::obtenerShaders]: Error en la apertura del archivo");
        }
        streamShader << archivoShader.rdbuf();
        _fsContent = streamShader.str();

        archivoShader.close();
    }

    void Shader::compilarVertexShader() {
        _idVS = glCreateShader(GL_VERTEX_SHADER);
        if(_idVS == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del vertex shader");
        }
        const GLchar* fuenteVS = _vsContent.c_str();
        glShaderSource(_idVS, 1, &fuenteVS, nullptr);
        glCompileShader(_idVS);

        //comprobamos que la compilacion del shader no ha sido un exito
        GLint vsCompilationSuccess;
        glGetShaderiv(_idVS, GL_COMPILE_STATUS, &vsCompilationSuccess);

        if (vsCompilationSuccess == GL_FALSE) {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(_idVS, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(_idVS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (vertex shader compilation)\n  " + mensaje);
        }
    }

    void Shader::compilarFragmentShader() {
        _idFS = glCreateShader(GL_FRAGMENT_SHADER);
        if(_idFS == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del Fragment shader");
        }
        const GLchar* fuenteFS = _fsContent.c_str();
        glShaderSource(_idFS, 1, &fuenteFS, nullptr);
        glCompileShader(_idFS);

        //comprobamos que la compilacion del shader no ha sido un exito
        GLint fsCompilationSuccess;
        glGetShaderiv(_idFS, GL_COMPILE_STATUS, &fsCompilationSuccess);
        if(fsCompilationSuccess == GL_FALSE) {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(_idFS, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(_idFS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (fragment shader compilation)\n  " + mensaje);
        }
    }

    void Shader::crearShaderProgram() {
        _idSP = glCreateProgram();
        if(_idSP == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del programa de shaders");
        }
        glAttachShader(_idSP, _idVS);
        glAttachShader(_idSP, _idFS);
        glLinkProgram(_idSP);

        GLint linkSuccess = 0;
        glGetProgramiv(_idSP, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE) {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(_idSP, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(_idSP, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (Program link)\n  " + mensaje);
        }
    }

    GLuint Shader::getProgramId() {
        return _idSP;
    }

    bool Shader::fail() {
        return _shaderFailure;
    }
} // PAG