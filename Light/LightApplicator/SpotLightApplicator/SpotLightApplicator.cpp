//
// Created by ahues on 24/11/2024.
//

#include "SpotLightApplicator.h"

namespace PAG {
    SpotLightApplicator::SpotLightApplicator(): LightApplicator() {

    }

    SpotLightApplicator::~SpotLightApplicator() {

    }

    void SpotLightApplicator::applyLight(LightProperties& properties, ShaderProgram& shaderProgram) {
        shaderProgram.setUniform("", properties._id);
        shaderProgram.setUniform("", properties._is);
        shaderProgram.setUniform("", properties._p);
        shaderProgram.setUniform("", properties._d);
        shaderProgram.setUniform("", properties._gamma);
        shaderProgram.setUniform("", properties._s);
    }
} // PAG