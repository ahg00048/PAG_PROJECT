//
// Created by ahues on 04/10/2024.
//

#ifndef PAG_PROJECT_SHADER_H
#define PAG_PROJECT_SHADER_H

#include <GLAD/glad.h>

namespace PAG {
    enum ShaderType {
        vertexShader = GL_VERTEX_SHADER,
        fragmentShader = GL_FRAGMENT_SHADER,
        geometryShader = GL_GEOMETRY_SHADER,
        undefined = 0
    };

    class Shader {
    private:
        GLuint _id;
        std::string _content;
        ShaderType _type;
    public:
        Shader();
        explicit Shader(ShaderType type);
        Shader(ShaderType type, const std::string& path);
        Shader(const Shader& orig);
        ~Shader();

        void setType(const ShaderType type);

        GLuint getId() const;
        ShaderType getType() const;

        void setContent(const std::string& content);
        void setContentFromFile(const std::string& path);

        void compile();

        bool empty() const;
        bool created() const;

        void deleteShader();
    };
} // PAG

#endif //PAG_PROJECT_SHADER_H
