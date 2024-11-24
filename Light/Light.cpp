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

    void Light::applyLight(ShaderProgram& shaderProgram) {
        if(_applicatorSelected == LightApplicatorType::_none)
            throw std::runtime_error("[Light::applyLight]: Type of light not chosen.");

        _applicators[_applicatorSelected]->applyLight(_properties, shaderProgram);
    }
} // PAG