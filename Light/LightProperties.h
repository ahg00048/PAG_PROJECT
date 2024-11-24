//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_LIGHTPROPERTIES_H
#define PAG_PROJECT_LIGHTPROPERTIES_H

#include <glm/vec3.hpp>

namespace PAG {
    struct LightProperties {
        glm::vec3 _ld;
        glm::vec3 _la;
        glm::vec3 _ls;
        glm::vec3 _p;
        glm::vec3 _d;
        float _gamma;
        float _s;
    };
}

#endif //PAG_PROJECT_LIGHTPROPERTIES_H
