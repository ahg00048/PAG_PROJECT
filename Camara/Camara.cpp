//
// Created by ahues on 11/10/2024.
//

#include "Camara.h"

#define MAX_FOV 45.0
#define MIN_FOV 1.0

namespace PAG {
    Camara::Camara():
        _zNear(0.0), _zFar(1.0), _angle(45.0), _scope(1.0),
        _left(-2.0), _right(2.0), _top(2.0), _botton(-2.0),
        _position(0.0, 0.0, 1.0), _target(0.0, 0.0, 0.0),
        _upVec(0.0, 1.0, 0.0) {

    }

    Camara::Camara(float zNear, float zFar,
                   float angle, float scope,
                   float left, float right, float top, float botton,
                   glm::vec3& position, glm::vec3& target, glm::vec3& upVec):
            _zNear(zNear), _zFar(zFar), _angle(angle), _scope(scope),
            _left(left), _right(right), _top(top), _botton(botton),
            _position(position), _target(target), _upVec(upVec) {

        if(_angle > MAX_FOV)
            _angle = MAX_FOV;
        if(_angle < MIN_FOV)
            _angle = MIN_FOV;
    }

    Camara::Camara(const Camara& orig):
        _zNear(orig._zNear), _zFar(orig._zFar), _angle(orig._angle), _scope(orig._scope),
        _left(orig._left), _right(orig._right), _top(orig._top), _botton(orig._botton),
        _position(orig._position), _target(orig._target), _upVec(orig._upVec) {

    }

    Camara::~Camara() {

    }

    const glm::mat4& Camara::getOrthographicProjection() const {
        return glm::ortho(_left, _right, _botton, _top, _zNear, _zFar);
    }

    const glm::mat4& Camara::getPerspectiveProjection() const {
        return glm::perspective(glm::radians(_angle), _scope, _zNear, _zFar);
    }

    const glm::mat4& Camara::getVision() const {
        return glm::lookAt(_position, _target, _upVec);
    }
//SETTERS
    void Camara::setZnear(float zNear) { _zNear = zNear; }
    void Camara::setZfar(float zFar) { _zFar = zFar; }
    //PERSP
    void Camara::setPerspectiveProjection(float zNear, float zFar, float angle, float scope) {
        _zNear = zNear;
        _zFar = zFar;
        _angle = angle;
        _scope = scope;
    }

    void Camara::setAngle(float angle) { _angle = angle; }
    void Camara::setScope(float scope) { _scope = scope; }
    //ORTHO
    void Camara::setOrthograpicProjection(float zNear, float zFar, float left, float right, float top, float botton) {
        _zNear = zNear;
        _zFar = zFar;
        _left = left;
        _right = right;
        _top = top;
        _botton = botton;
    }

    void Camara::setLeft(float left) { _left = left; }
    void Camara::setRight(float right) { _right = right; }
    void Camara::setBotton(float botton) { _botton = botton; }
    void Camara::setTop(float top) { _top = top; }
//GETTERS
    float Camara::getZnear() const { return _zNear; }
    float Camara::getZfar() const { return _zFar; }
    //PERSP
    float Camara::getAngle() const { return _angle; }
    float Camara::getScope() const { return _scope; }
    //ORTHO
    float Camara::getLeft() const { return _left; }
    float Camara::getRight() const { return _right; }
    float Camara::getBotton() const { return _botton; }
    float Camara::getTop() const { return _top; }
//-------
//MOVEMENTS
    void Camara::tilt(float angle) {
        //Calculamos matriz de transformacion
        glm::mat4 transform = glm::translate(_position) *
                glm::rotate(glm::radians(angle), glm::normalize(glm::cross(_upVec, _position - _target))) *
                glm::translate(-_position);
        //Rotamos el punto de mira y el vector UP
        _target = transform * glm::vec4(_target, 1.0f);
        _upVec = transform * glm::vec4(_upVec, 0.0f);
    }

    void Camara::pan(float angle) {
        //Calculamos matriz de transformacion
        glm::mat4 transform = glm::translate(_position) *
                glm::rotate(glm::radians(angle), _upVec) *
                glm::translate(-_position);
        //Rotamos el punto de mira y el vector UP
        _target = transform * glm::vec4(_target, 1.0f);
    }

    void Camara::dolly(float xMovement, float zMovement) {
        _target.x += xMovement;
        _target.z += zMovement;

        _position.x += xMovement;
        _position.z += zMovement;
    }

    void Camara::orbit(float yAngle, float xAngle) {
        glm::mat4 transform = glm::translate(_target) *
                            glm::rotate(glm::radians(xAngle), _upVec) *
                            glm::rotate(glm::radians(yAngle), glm::normalize(glm::cross(_upVec, _position - _target))) *
                            glm::translate(-_target);

        _position = transform * glm::vec4(_position, 1.0f);
        _upVec = transform * glm::vec4(_upVec, 0.0f);
    }

    void Camara::crane(float yMovement) {
        _target.y += yMovement;

        _position.y += yMovement;
    }

    void Camara::zoom(float angle) {
        _angle += angle;

        if(_angle > MAX_FOV)
            _angle = MAX_FOV;
        if(_angle < MIN_FOV)
            _angle = MIN_FOV;
    }
} // PAG