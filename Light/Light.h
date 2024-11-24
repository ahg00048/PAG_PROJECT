//
// Created by ahues on 24/11/2024.
//

#ifndef PAG_PROJECT_LIGHT_H
#define PAG_PROJECT_LIGHT_H

#include <array>

#include "LightApplicator/DirectionaLightApplicator/DirectionalLightApplicator.h"
#include "LightApplicator/SpotLightApplicator/SpotLightApplicator.h"
#include "LightApplicator/PointLightApplicator/PointLightApplicator.h"
#include "LightApplicator/AmbientLightApplicator/AmbientLightApplicator.h"

namespace PAG {
    class Light {
    private:
        LightProperties _properties;
        LightApplicatorType _applicatorSelected;
        std::array<LightApplicator*, NUM_LIGHT_APPLICATORS> _applicators;
    public:
        Light();
        ~Light();
        void setLightApplicator(LightApplicatorType applicatorSelected);
        void applyLight(ShaderProgram& shaderProgram);
    };
} // PAG

#endif //PAG_PROJECT_LIGHT_H
