//
// Created by ahues on 14/11/2024.
//

#ifndef PAG_PROJECT_MATERIAL_H
#define PAG_PROJECT_MATERIAL_H

#include <glm/vec3.hpp>

namespace PAG {
    class Material {
    private:
        glm::vec3 _diffuse, _ambient, _specular;
        float _phongExp;
    public:
        Material();
        Material(const Material& orig);
        Material(const glm::vec3& diffuse, const glm::vec3& ambient, const glm::vec3& specular, float phongExp);
        ~Material();

        void setDiffuse(const glm::vec3& diffuse);
        void setAmbient(const glm::vec3& ambient);
        void setSpecular(const glm::vec3& specular);
        void setPhongExp(float phongExp);

        const glm::vec3& getDiffuse() const;
        const glm::vec3& getAmbient() const;
        const glm::vec3& getSpecular() const;
        float getPhongExp() const;
    };
} // PAG

#endif //PAG_PROJECT_MATERIAL_H
