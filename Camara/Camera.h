//
// Created by ahues on 11/10/2024.
//

#ifndef PAG_PROJECT_CAMERA_H
#define PAG_PROJECT_CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#define TILT_DEFAULT_SPEED  15.0f
#define PAN_DEFAULT_SPEED   15.0f
#define CRANE_DEFAULT_SPEED  1.0f
#define DOLLY_DEFAULT_SPEED  1.0f
#define ORBIT_DEFAULT_SPEED 30.0f
#define ZOOM_DEFAULT_SPEED  10.0f

#define PAG_PERSP_PROJ true
#define PAG_ORTHO_PROJ false

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

        bool _perspProj;

        const glm::mat4 getOrthographicProjection() const;
        const glm::mat4 getPerspectiveProjection() const;

        void zoomOrtho(float offset);
        void zoomPersp(float angle);

        void checkAngle();
        void checkZBorders();
        void checkLeftRight();
        void checkTopBotton();
        void checkOrthoExclusiveSettings();
        void checkSettings();
    public:
        Camera();
        Camera(float zNear, float zFar,
               float angle, float scope,
               float left, float right, float top, float botton,
               glm::vec3& position, glm::vec3& target, glm::vec3& upVec, bool perspProj = true);
        Camera(const Camera& orig);
        ~Camera();

        const glm::mat4 getProjection() const;
        const glm::mat4 getVision() const;

        void orthoParamsFromPersp();
        void perspParamsFromOrtho();

        void setPerspectiveProjection(float zNear, float zFar, float angle, float scope);
        void setPerspectiveProjection(float angle, float scope);
        void setOrthographicProjection(float zNear, float zFar, float left, float right, float top, float botton);
        void setOrthographicProjection(float left, float right, float top, float botton);

        void setProjType(bool perspProj);
        void setZnear(float zNear);
        void setZfar(float zFar);
        void setAngle(float angle);
        void setScope(float scope);
        void setLeft(float left);
        void setRight(float right);
        void setBotton(float botton);
        void setTop(float top);

        void setTarget(const glm::vec3& target);

        bool getProjType() const;
        float getZnear() const;
        float getZfar() const;
        float getAngle() const;
        float getScope() const;
        float getLeft() const;
        float getRight() const;
        float getBotton() const;
        float getTop() const;

        void tilt(float angle);
        void pan(float angle);
        void dolly(float xMovement, float zMovement);
        void orbit(float xAngle, float yAngle);
        void crane(float yMovement);
        void zoom(float value);
    };
} // PAG

#endif //PAG_PROJECT_CAMERA_H
