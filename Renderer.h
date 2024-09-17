//
// Created by ahues on 20/09/2024.
//

#ifndef PAG_PROJECT_RENDERER_H
#define PAG_PROJECT_RENDERER_H

#include <glm/vec4.hpp>

namespace PAG {

    class Renderer {
    private:
        static Renderer* _singleton;

    public:
        static Renderer& getRenderer();
        Renderer();
        void refrescar();
    };

} // PAG

#endif //PAG_PROJECT_RENDERER_H
