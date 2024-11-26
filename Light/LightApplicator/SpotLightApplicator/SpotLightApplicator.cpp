//
// Created by ahues on 24/11/2024.
//

#include "SpotLightApplicator.h"

namespace PAG {
    SpotLightApplicator::SpotLightApplicator(): LightApplicator() {

    }

    SpotLightApplicator::~SpotLightApplicator() {

    }

    void SpotLightApplicator::applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) {
        glm::vec3 dir = glm::vec3(vision * glm::vec4(properties._d, 0.0f));
        glm::vec3 pos = glm::vec3(vision * glm::vec4(properties._p, 1.0f));

        shaderProgram.setUniform("Id", properties._dI);
        shaderProgram.setUniform("Is", properties._sI);
        shaderProgram.setUniform("lightPos", pos);
        shaderProgram.setUniform("lightDir", dir);
        shaderProgram.setUniform("gamma", glm::radians(properties._gamma));
        shaderProgram.setUniform("s", properties._s);
        shaderProgram.setUniformSubroutine("spotlight", ShaderType::fragmentShader);
    }
} // PAG