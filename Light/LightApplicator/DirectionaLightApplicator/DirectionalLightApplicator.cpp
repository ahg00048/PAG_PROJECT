//
// Created by ahues on 24/11/2024.
//

#include "DirectionalLightApplicator.h"

namespace PAG {
    DirectionalLightApplicator::DirectionalLightApplicator(): LightApplicator() {

    }

    DirectionalLightApplicator::~DirectionalLightApplicator() {

    }

    void DirectionalLightApplicator::applyLight(LightProperties &properties, ShaderProgram &shaderProgram) {
        shaderProgram.setUniform("", properties._d);
        shaderProgram.setUniform("", properties._is);
        shaderProgram.setUniform("", properties._id);
    }
} // PAG