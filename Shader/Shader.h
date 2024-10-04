//
// Created by ahues on 04/10/2024.
//

#ifndef PAG_PROJECT_SHADER_H
#define PAG_PROJECT_SHADER_H

#include <GLAD/glad.h>

namespace PAG {
    class Shader {
    private:
        GLuint _idVS = 0;
        GLuint _idFS = 0;
        GLuint _idSP = 0;

        std::string _vsContent = "";
        std::string _fsContent = "";

        bool _shaderFailure = false;
    public:
        Shader();
        ~Shader();

        void cargarShaders(const std::string& path);
        void compilarVertexShader();
        void compilarFragmentShader();
        void crearShaderProgram();

        GLuint getProgramId();

        bool fail();
    };
} // PAG

#endif //PAG_PROJECT_SHADER_H
