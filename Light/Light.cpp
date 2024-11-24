//
// Created by ahues on 24/11/2024.
//

#include "Light.h"

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
            return;

        _applicators[_applicatorSelected]->applyLight(_properties, shaderProgram);
    }
} // PAG