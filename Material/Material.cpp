//
// Created by ahues on 14/11/2024.
//

#include "Material.h"

namespace PAG {
    Material::Material():
        _diffuse(), _ambient(), _specular(), _phongExp(0.0f) {

    }

    Material::Material(const Material& orig):
        _diffuse(orig._diffuse), _ambient(orig._ambient),
        _specular(orig._specular), _phongExp(orig._phongExp) {

    }

    Material::Material(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, float phongExp):
            _diffuse(diffuse), _ambient(ambient),
            _specular(specular), _phongExp(phongExp) {

    }

    Material::~Material() {

    }

    void Material::setDiffuse(const glm::vec3& diffuse) { _diffuse = diffuse; }
    void Material::setAmbient(const glm::vec3& ambient) { _ambient = ambient; }
    void Material::setSpecular(const glm::vec3& specular) { _specular = specular; }
    void Material::setPhongExp(float phongExp) { _phongExp = phongExp; }

    const glm::vec3& Material::getDiffuse() const { return _diffuse; }
    const glm::vec3& Material::getAmbient() const { return _ambient; }
    const glm::vec3& Material::getSpecular() const { return _specular; }
    float Material::getPhongExp() const { return _phongExp; }
} // PAG