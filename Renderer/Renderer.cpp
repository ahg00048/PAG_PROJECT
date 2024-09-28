//
// Created by ahues on 20/09/2024.
//

#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "Renderer.h"

#define ENTRELAZADO true

namespace PAG {
    Renderer* Renderer::_singleton = nullptr;

    Renderer& Renderer::getRenderer() {
        if(!_singleton)
            _singleton = new Renderer();
        return *_singleton;
    }

    Renderer::Renderer() {
        _clearColor = glm::vec4(0.6, 0.6, 0.6, 1.0);
    }

    Renderer::~Renderer() {
        if(idVS != 0)
            glDeleteShader(idVS);
        if(idFS != 0)
            glDeleteShader(idFS);
        if (idSP != 0)
            glDeleteProgram(idSP);
        if (idVBO != 0)
            glDeleteBuffers(1, &idVBO);
        if (idIBO != 0)
            glDeleteBuffers(1, &idIBO);
        if (idVAO != 0)
            glDeleteVertexArrays(1, &idVAO );
    }

    void Renderer::init() {
        glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_MULTISAMPLE);
    }

    void Renderer::setClearColor(glm::vec4& newColor) {
        this->_clearColor = newColor;
    }

    void Renderer::setClearColor(float R, float G, float B, float A) {
        this->_clearColor = glm::vec4(R,G,B,A);
    }

    glm::vec4 Renderer::getClearColor() {
        return this->_clearColor;
    }

    void Renderer::creaShaderProgram() {
      idVS = glCreateShader(GL_VERTEX_SHADER);
        if(idVS == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del vertex shader");
        }
        const GLchar* fuenteVS = _vsContent.c_str();
        glShaderSource(idVS, 1, &fuenteVS, nullptr);
        glCompileShader(idVS);

        //comprobamos que la compilacion del shader no ha sido un exito
        GLint vsCompilationSuccess;
        glGetShaderiv(idVS, GL_COMPILE_STATUS, &vsCompilationSuccess);

        if (vsCompilationSuccess == GL_FALSE) {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idVS, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idVS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (vertex shader compilation)\n  " + mensaje);
        }

        idFS = glCreateShader(GL_FRAGMENT_SHADER);
        if(idFS == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del Fragment shader");
        }
        const GLchar* fuenteFS = _fsContent.c_str();
        glShaderSource(idFS, 1, &fuenteFS, nullptr);
        glCompileShader(idFS);

        //comprobamos que la compilacion del shader no ha sido un exito
        GLint fsCompilationSuccess;
        glGetShaderiv(idVS, GL_COMPILE_STATUS, &fsCompilationSuccess);
        if(fsCompilationSuccess == GL_FALSE) {  // Ha habido un error en la compilación.
            // Para saber qué ha pasado, tenemos que recuperar el mensaje de error de OpenGL
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv(idFS, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog(idFS, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (fragment shader compilation)\n  " + mensaje);
        }

        idSP = glCreateProgram();
        if(idSP == 0) {
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: Error en la creación del programa de shaders");
        }
        glAttachShader(idSP, idVS);
        glAttachShader(idSP, idFS);
        glLinkProgram(idSP);

        GLint linkSuccess = 0;
        glGetProgramiv(idSP, GL_LINK_STATUS, &linkSuccess);
        if(linkSuccess == GL_FALSE) {  // Ha habido un error y hay que recuperar su descripción, para saber qué ha pasado
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &tamMsj);
            // Comprobamos que el mensaje no sea nulo
            if(tamMsj > 0) {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetProgramInfoLog(idSP, tamMsj, &datosEscritos, mensajeFormatoC);
                mensaje.assign(mensajeFormatoC);
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;
            }
            _shaderFailure = true;
            throw std::runtime_error("[PAG::Renderer::creaShaderProgram]: (Program link)\n  " + mensaje);
        }
    }

    void Renderer::obtenerShaders(const std::string& path) {
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

    void Renderer::creaModelo() {
        // Geometria
        //con un solo VBO entrelazado
        GLfloat verticesAndColors[] = {-.5, -.5, 0,     1.0, 0.0, 0.0,
                                        .5, -.5, 0,      0.0, 1.0,0.0,
                                        .0, .5, 0,    0.0, 0.0,1.0};
        //con dos VBO no entrelazados
        GLfloat vertices[] = {-.5, -.5, 0,
                               .5, -.5, 0,
                               .0, .5, 0};

        GLfloat colors[] = {1.0, 0.0, 0.0,
                            0.0, 1.0,0.0,
                            0.0, 0.0,1.0};
        // Topologia
        GLuint indices[] = {0, 1, 2};

        // Generamos el VAO
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        // Generamos el VBO
#if ENTRELAZADO
        // VBO ENTRELAZADO
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);

        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), verticesAndColors, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
#else
        // VBOS NO ENTRELAZADOS
        glGenBuffers(2, _idVBOs);
        glBindBuffer(GL_ARRAY_BUFFER,  _idVBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,  _idVBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(1);
#endif
        // Generamos el IBO
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices,
                       GL_STATIC_DRAW);
    }

    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(_clearColor[0],_clearColor[1], _clearColor[2],_clearColor[3]);

        if(_shaderFailure)
            return;

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(idSP);
        glBindVertexArray(idVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::ratonRueda(double xoffset, double yoffset) {
        //yoffset es 0 si la rueda del raton no esta en movimiento, -1 cuando gira hacia abajo, 1 hacia arriba
        float slope = 0.015f;

        if (yoffset < 0){
            float min = _clearColor[0];
            for(int i = 0; i < glm::vec4::length() - 1; i++) {
                _clearColor[i] -= slope;
                if(min > _clearColor[i])
                    min = _clearColor[i];
            }

            if(min < 0)
                for(int i = 0; i < glm::vec4::length() - 1; i++)
                    if(_clearColor[i] < 0)
                        _clearColor[i] -= min;

        }else if(yoffset > 0) {
            float max = -1;
            for(int i = 0; i < glm::vec4::length() - 1; i++) {
                _clearColor[i] += slope;
                if(max < _clearColor[i])
                    max = _clearColor[i];
            }

            if(max > 1)
                for(int i = 0; i < glm::vec4::length() - 1; i++)
                    _clearColor[i] /= max;

        }
    }

    void Renderer::tamanoViewport(int width, int height) {
        glViewport(0, 0, width, height);
    }

    std::string Renderer::getInforme() {
        std::string resultado;

        resultado.append((const char*)glGetString(GL_RENDERER));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_VENDOR));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_VERSION));
        resultado.push_back('\n');
        resultado.append((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

        return resultado;
    }
} // PAG