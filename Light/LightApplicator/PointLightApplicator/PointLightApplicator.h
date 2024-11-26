//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_POINTLIGHTAPPLICATOR_H
#define PAG_PROJECT_POINTLIGHTAPPLICATOR_H

#include "../LightApplicator.h"

namespace PAG {
    class PointLightApplicator : public LightApplicator {
    public:
        PointLightApplicator();
        ~PointLightApplicator();
        void applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) override;
    };
} // PAG

#endif //PAG_PROJECT_POINTLIGHTAPPLICATOR_H
