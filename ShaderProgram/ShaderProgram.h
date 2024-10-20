//
// Created by ahues on 19/10/2024.
//

#ifndef PAG_PROJECT_SHADERPROGRAM_H
#define PAG_PROJECT_SHADERPROGRAM_H

#include <vector>
#include <map>
#include <string>

#include "../Shader/Shader.h"

namespace PAG {

    class ShaderProgram {
    private:
        std::map<ShaderType, Shader> _shaders;
        GLuint _id;

        bool shaderAttached(GLuint shader);
    public:
        ShaderProgram();
        ShaderProgram(const ShaderProgram& orig);
        ~ShaderProgram();

        GLuint getId() const;
        std::vector<Shader*> getShaders();
        std::vector<Shader*> getEmptyShaders();

        void createShaderProgram();

        void addShader(Shader&& shader);
    };

} // PAG

#endif //PAG_PROJECT_SHADERPROGRAM_H
