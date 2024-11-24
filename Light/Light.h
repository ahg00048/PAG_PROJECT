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

        void setDI(const glm::vec3& DI);
        void setAI(const glm::vec3& AI);
        void setSI(const glm::vec3& SI);
        void setPosition(const glm::vec3& pos);
        void setDirection(const glm::vec3& dir);
        void setGamma(float gamma);
        void setAttenuation(float s);

        const glm::vec3& getDI();
        const glm::vec3& getAI();
        const glm::vec3& getSI();
        const glm::vec3& getPostition();
        const glm::vec3& getDirection();
        float getGamma();
        float getAttenuation();

        void setLightApplicator(LightApplicatorType applicatorSelected);
        void applyLight(ShaderProgram& shaderProgram);
    };
} // PAG

#endif //PAG_PROJECT_LIGHT_H
