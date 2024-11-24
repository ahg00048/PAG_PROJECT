//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_DIRECTIONALLIGHTAPPLICATOR_H
#define PAG_PROJECT_DIRECTIONALLIGHTAPPLICATOR_H

#include "../LightApplicator.h"

namespace PAG {
    class DirectionalLightApplicator : public LightApplicator {
    public:
        DirectionalLightApplicator();
        ~DirectionalLightApplicator();
        void applyLight(LightProperties& properties, ShaderProgram& shaderProgram) override;
    };
} // PAG

#endif //PAG_PROJECT_DIRECTIONALLIGHTAPPLICATOR_H
