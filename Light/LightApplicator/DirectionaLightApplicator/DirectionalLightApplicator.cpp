//
// Created by ahues on 24/11/2024.
//

#include "DirectionalLightApplicator.h"

namespace PAG {
    DirectionalLightApplicator::DirectionalLightApplicator(): LightApplicator() {

    }

    DirectionalLightApplicator::~DirectionalLightApplicator() {

    }

    void DirectionalLightApplicator::applySubroutine(ShaderProgram& shaderProgram) {
        shaderProgram.setUniformSubroutine("directional", ShaderType::fragmentShader);
    }

    void DirectionalLightApplicator::applyLight(LightProperties &properties, const glm::mat4& vision, ShaderProgram &shaderProgram) {
        glm::vec3 dir = glm::vec3(vision * glm::vec4(properties._d, 0.0f));

        shaderProgram.setUniform("lightDir", dir);
        shaderProgram.setUniform("Is", properties._sI);
        shaderProgram.setUniform("Id", properties._dI);
    }
} // PAG