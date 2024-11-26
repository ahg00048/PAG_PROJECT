//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_AMBIENTLIGHTAPPLICATOR_H
#define PAG_PROJECT_AMBIENTLIGHTAPPLICATOR_H

#include "../LightApplicator.h"

namespace PAG {
    class AmbientLightApplicator : public LightApplicator {
    public:
        AmbientLightApplicator();
        ~AmbientLightApplicator();
        void applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) override;
    };
} // PAG

#endif //PAG_PROJECT_AMBIENTLIGHTAPPLICATOR_H
