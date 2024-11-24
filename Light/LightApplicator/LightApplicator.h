//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_LIGHTAPPLICATOR_H
#define PAG_PROJECT_LIGHTAPPLICATOR_H

#define NUM_LIGHT_APPLICATORS 4

#include "../LightProperties.h"
#include "../../ShaderProgram/ShaderProgram.h"

namespace PAG {
    enum LightApplicatorType {
        _none = -1,
        _pointLight = 0,
        _spotLight,
        _directionalLight,
        _ambientLight
    };

    class LightApplicator {
    public:
        LightApplicator() = default;
        virtual ~LightApplicator() = default;
        virtual void applyLight(LightProperties& properties, ShaderProgram& shaderProgram) = 0;
    };
}

#endif //PAG_PROJECT_LIGHTAPPLICATOR_H