//
// Created by ahues on 11/10/2024.
//

#ifndef PAG_PROJECT_CAMARA_H
#define PAG_PROJECT_CAMARA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>

#include <string>

namespace PAG {
    class Camara {
    private:
        float _zNear, _zFar;
        //perspective exclusive atributes
        float _angle, _scope;
        //orthographic exclusive atributes
        float _left, _right, _top, _botton;
        glm::vec3 _position, _target, _upVec;
    public:
        Camara();
        Camara(float zNear, float zFar,
               float angle, float scope,
               float left, float right, float top, float botton,
               glm::vec3& position, glm::vec3& target, glm::vec3& upVec);
        Camara(const Camara& orig);
        ~Camara();

        const glm::mat4& getOrthographicProjection() const;
        const glm::mat4& getPerspectiveProjection() const;
        const glm::mat4& getVision() const;

        void setZnear(float zNear);
        void setZfar(float zFar);
        void setAngle(float angle);
        void setScope(float scope);
        void setLeft(float left);
        void setRight(float right);
        void setBotton(float botton);
        void setTop(float top);

        float getZnear() const;
        float getZfar() const;
        float getAngle() const;
        float getScope() const;
        float getLeft() const;
        float getRight() const;
        float getBotton() const;
        float getTop() const;

        void setPerspectiveProjection(float zNear, float zFar, float angle, float scope);
        void setOrthograpicProjection(float zNear, float zFar, float left, float right, float top, float botton);

        void tilt(float angle);
        void pan(float angle);
        void dolly(float xMovement, float zMovement);
        void orbit(float yAngle, float xAngle);
        void crane(float yMovement);
        void zoom(float angle);
    };
} // PAG

#endif //PAG_PROJECT_CAMARA_H
