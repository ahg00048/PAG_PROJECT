//
// Created by ahues on 24/11/2024.
//

#include "AmbientLightApplicator.h"

namespace PAG {
    AmbientLightApplicator::AmbientLightApplicator() : LightApplicator() {

    }

    AmbientLightApplicator::~AmbientLightApplicator() {

    }

    void AmbientLightApplicator::applyLight(PAG::LightProperties &properties, const glm::mat4& vision, PAG::ShaderProgram &shaderProgram) {
        shaderProgram.setUniform("Ia", properties._aI);
        shaderProgram.setUniformSubroutine("ambient", ShaderType::fragmentShader);
    }
} // PAG