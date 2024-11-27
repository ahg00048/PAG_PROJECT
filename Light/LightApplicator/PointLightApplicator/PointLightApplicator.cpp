//
// Created by ahues on 24/11/2024.
//

#include "PointLightApplicator.h"

namespace PAG {
    PointLightApplicator::PointLightApplicator(): LightApplicator(){

    }

    PointLightApplicator::~PointLightApplicator() {

    }

    void PointLightApplicator::applySubroutine(ShaderProgram& shaderProgram) {
        shaderProgram.setUniformSubroutine("point", ShaderType::fragmentShader);
    }

    void PointLightApplicator::applyLight(LightProperties& properties, const glm::mat4& vision, ShaderProgram& shaderProgram) {
        glm::vec3 pos = glm::vec3(vision * glm::vec4(properties._p, 1.0f));

        shaderProgram.setUniform("lightPos", pos);
        shaderProgram.setUniform("Is", properties._sI);
        shaderProgram.setUniform("Id", properties._dI);
    }
} // PAG