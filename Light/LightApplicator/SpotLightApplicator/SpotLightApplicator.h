//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_SPOTLIGHTAPPLICATOR_H
#define PAG_PROJECT_SPOTLIGHTAPPLICATOR_H

#include "../LightApplicator.h"

namespace PAG {
    class SpotLightApplicator : public LightApplicator {
    public:
        SpotLightApplicator();
        ~SpotLightApplicator();
        void applySubroutine(ShaderProgram& shaderProgram);
        void applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) override;
    };
} // PAG

#endif //PAG_PROJECT_SPOTLIGHTAPPLICATOR_H
