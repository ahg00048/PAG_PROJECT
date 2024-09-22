//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <glad/glad.h>

namespace PAG {
    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;
        Renderer();
    public:
        virtual ~Renderer();
        void init();
        static Renderer& getRenderer();
        void setClearColor(glm::vec4& newColor);
        void setClearColor(float R, float G, float B, float A);
        glm::vec4 getClearColor();
        void refrescar();
        void ratonRueda(double xoffset, double yoffset);
        void render();
        void tamanoViewport(int width, int height);
    };
} // PAG

#endif //PAG_PROJECT_RENDERER_H
