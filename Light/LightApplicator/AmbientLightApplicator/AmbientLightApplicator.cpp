//
// Created by ahues on 24/11/2024.
//

#include "AmbientLightApplicator.h"

namespace PAG {
    AmbientLightApplicator::AmbientLightApplicator() : LightApplicator() {

    }

    AmbientLightApplicator::~AmbientLightApplicator() {

    }

    void AmbientLightApplicator::applyLight(PAG::LightProperties &properties, PAG::ShaderProgram &shaderProgram) {
        shaderProgram.setUniform("", properties._ia);
    }
} // PAG