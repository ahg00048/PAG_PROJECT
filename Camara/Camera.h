//
// Created by ahues on 11/10/2024.
//

#ifndef PAG_PROJECT_CAMERA_H
#define PAG_PROJECT_CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#define TILT_DEFAULT_SPEED  15.0f
#define PAN_DEFAULT_SPEED   15.0f
#define CRANE_DEFAULT_SPEED  0.5f
#define DOLLY_DEFAULT_SPEED  0.5f
#define ORBIT_DEFAULT_SPEED 15.0f
#define ZOOM_DEFAULT_SPEED   5.0f

#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/epsilon.hpp>

#include <string>

namespace PAG {
    enum CameraMove {
        TILT = 0,
        PAN,
        CRANE,
        DOLLY,
        ORBIT,
        ZOOM
    };

    class Camera {
    private:
        float _zNear, _zFar;
        //perspective exclusive atributes
        float _angle, _scope;
        //orthographic exclusive atributes
        float _left, _right, _top, _botton;
        glm::vec3 _position, _target, _upVec;
    public:
        Camera();
        Camera(float zNear, float zFar,
               float angle, float scope,
               float left, float right, float top, float botton,
               glm::vec3& position, glm::vec3& target, glm::vec3& upVec);
        Camera(const Camera& orig);
        ~Camera();

        const glm::mat4 getOrthographicProjection() const;
        const glm::mat4 getPerspectiveProjection() const;
        const glm::mat4 getVision() const;

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

        void setTarget(const glm::vec3& target);

        void tilt(float angle);
        void pan(float angle);
        void dolly(float xMovement, float zMovement);
        void orbit(float xAngle, float yAngle);
        void crane(float yMovement);
        void zoom(float angle);
    };
} // PAG

#endif //PAG_PROJECT_CAMERA_H
