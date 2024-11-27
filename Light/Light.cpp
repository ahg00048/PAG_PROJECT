//
// Created by ahues on 24/11/2024.
//

#include "Light.h"

#include <stdexcept>

namespace PAG {
    Light::Light(): _applicatorSelected(LightApplicatorType::_none), _properties() {
        _applicators[0] = new PointLightApplicator;
        _applicators[1] = new SpotLightApplicator;
        _applicators[2] = new DirectionalLightApplicator;
        _applicators[3] = new AmbientLightApplicator;
    }

    Light::~Light() {
        for(LightApplicator* applicator : _applicators)
            delete applicator;
    }

    void Light::setLightApplicator(LightApplicatorType applicatorSelected) {
        _applicatorSelected = applicatorSelected;
    }

    void Light::setSubroutine(ShaderProgram& shaderProgram) {
        if(_applicatorSelected == LightApplicatorType::_none)
            throw std::runtime_error("[Light::applyLight]: Type of light not chosen.");

        _applicators[_applicatorSelected]->applySubroutine(shaderProgram);
    }

    void Light::applyLight(ShaderProgram& shaderProgram) {
        if(_applicatorSelected == LightApplicatorType::_none)
            throw std::runtime_error("[Light::applyLight]: Type of light not chosen.");

        _applicators[_applicatorSelected]->applyLight(_properties, _vision, shaderProgram);
    }

    void Light::setDI(const glm::vec3& DI) { _properties._dI = DI; }
    void Light::setAI(const glm::vec3& AI) { _properties._aI = AI; }
    void Light::setSI(const glm::vec3& SI) { _properties._sI = SI; }
    void Light::setPosition(const glm::vec3& pos) { _properties._p = pos; }
    void Light::setDirection(const glm::vec3& dir) { _properties._d = dir; }
    void Light::setGamma(float gamma) { _properties._gamma = gamma; }
    void Light::setAttenuation(float s) { _properties._s = s; }
    void Light::setVision(const glm::mat4& vision) { _vision = vision; }

    const glm::vec3& Light::getDI() { return _properties._dI; }
    const glm::vec3& Light::getAI() { return _properties._aI; }
    const glm::vec3& Light::getSI() { return _properties._sI; }
    const glm::vec3& Light::getPostition() { return _properties._p; }
    const glm::vec3& Light::getDirection() { return _properties._d; }
    float Light::getGamma() { return _properties._gamma; }
    float Light::getAttenuation() { return _properties._s; }
    const glm::mat4& Light::getVision() { return _vision; }
} // PAG