//
// Created by ahues on 24/11/2024.
//

#include "PointLightApplicator.h"

namespace PAG {
    PointLightApplicator::PointLightApplicator(): LightApplicator(){

    }

    PointLightApplicator::~PointLightApplicator() {

    }

    void PointLightApplicator::applyLight(LightProperties& properties, ShaderProgram& shaderProgram) {
        shaderProgram.setUniform("", properties._p);
        shaderProgram.setUniform("", properties._is);
        shaderProgram.setUniform("", properties._id);
    }
} // PAG