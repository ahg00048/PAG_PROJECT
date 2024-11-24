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
        void applyLight(LightProperties& properties, ShaderProgram& shaderProgram) override;
    };
} // PAG

#endif //PAG_PROJECT_SPOTLIGHTAPPLICATOR_H