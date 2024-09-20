//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>
#include <gl/gl.h>

namespace PAG {

    class Renderer {
    private:
        static Renderer* _singleton;
        glm::vec4 _clearColor;
    public:
        static Renderer& getRenderer();
        Renderer();
        ~Renderer();
        void setClearColor(glm::vec4 newColor);
        void setClearColor(float R, float G, float B, float A);
        glm::vec4 getClearColor();
        void refrescar();
        void tecla();
        void ratonBoton();
        void ratonRueda();
        void tamanoViewport(int width, int height);
    };

} // PAG

#endif //PAG_PROJECT_RENDERER_H
