//
// Created by ahues on 11/10/2024.
//

#include "Camera.h"

#define MAX_FOV 90.0
#define MIN_FOV 1.0
#define MIN_Z_NEAR 0.01

namespace PAG {
    Camera::Camera():
        _zNear(0.1f), _zFar(100.0f), _angle(45.0f), _scope(1.0f),
        _left(-2.0f), _right(2.0f), _top(2.0f), _botton(-2.0f),
        _position(0.0f, 0.0f, 5.0f), _target(0.0f, 0.0f, 0.0f),
        _upVec(0.0f, 1.0f, 0.0f), _perspProj(true) {

    }

    Camera::Camera(float zNear, float zFar, float angle, float scope,
                   float left, float right, float top, float botton,
                   glm::vec3& position, glm::vec3& target, glm::vec3& upVec, bool perspProj):
            _perspProj(perspProj),
            _zNear(zNear), _zFar(zFar), _angle(angle), _scope(scope),
            _left(left), _right(right), _top(top), _botton(botton),
            _position(position), _target(target), _upVec(upVec) {
        checkSettings();
    }

    Camera::Camera(const Camera& orig): _perspProj(orig._perspProj),
        _zNear(orig._zNear), _zFar(orig._zFar), _angle(orig._angle), _scope(orig._scope),
        _left(orig._left), _right(orig._right), _top(orig._top), _botton(orig._botton),
        _position(orig._position), _target(orig._target), _upVec(orig._upVec) {

    }

    Camera::~Camera() {

    }

    void Camera::checkSettings() {
        checkZBorders();
        checkAngle();
        checkOrthoExclusiveSettings();
    }

    void Camera::checkAngle() {
        if(_angle > MAX_FOV)
            _angle = MAX_FOV;
        if(_angle < MIN_FOV)
            _angle = MIN_FOV;
    }

    void Camera::checkZBorders() {
        if(_zNear < MIN_Z_NEAR)
            _zNear = MIN_Z_NEAR;

        if(_zFar < _zNear)
            _zFar = _zNear;
    }

    void Camera::checkOrthoExclusiveSettings() {
        checkLeftRight();
        checkTopBotton();
    }

    void Camera::checkLeftRight() {
        if(_left > _right)
            _left = _right = 0;
    }

    void Camera::checkTopBotton() {
        if(_top < _botton)
            _top = _botton = 0;
    }

    void Camera::orthoParamsFromPersp() {
        float height = glm::tan(glm::radians(_angle / 2)) * _zFar;
        _botton = -height;
        _top = height;
        _left = -height * _scope;
        _right = height * _scope;
    }

    void Camera::perspParamsFromOrtho() {
        float height = (_top - _botton) / 2;

        _scope = glm::abs(_left) / height;
        _angle = glm::degrees(glm::atan(height / _zFar) * 2);
    }

    const glm::mat4 Camera::getOrthographicProjection() const {
        return glm::ortho(_left, _right, _botton, _top, _zNear, _zFar);
    }

    const glm::mat4 Camera::getPerspectiveProjection() const {
        return glm::perspective(glm::radians(_angle), _scope, _zNear, _zFar);
    }

    const glm::mat4 Camera::getProjection() const {
        return (_perspProj) ? getPerspectiveProjection() : getOrthographicProjection();
    }

    const glm::mat4 Camera::getVision() const {
        return glm::lookAt(_position, _target, _upVec);
    }
//SETTERS
    void Camera::setProjType(bool perspProj) {
        _perspProj = perspProj;
    }

    void Camera::setTarget(const glm::vec3& target) { _target = target; }

    void Camera::setZnear(float zNear) { _zNear = zNear; }
    void Camera::setZfar(float zFar) { _zFar = zFar; }
    //PERSP
    void Camera::setPerspectiveProjection(float zNear, float zFar, float angle, float scope) {
        _zNear = zNear;
        _zFar = zFar;
        _angle = angle;
        _scope = scope;

        checkZBorders();
        checkAngle();
    }

    void Camera::setPerspectiveProjection(float angle, float scope) {
        _angle = angle;
        _scope = scope;

        checkAngle();
    }

    void Camera::setAngle(float angle) {
        _angle = angle;
        checkAngle();
    }

    void Camera::setScope(float scope) { _scope = scope; }
    //ORTHO
    void Camera::setOrthographicProjection(float zNear, float zFar, float left, float right, float top, float botton) {
        _zNear = zNear;
        _zFar = zFar;
        _left = left;
        _right = right;
        _top = top;
        _botton = botton;

        checkZBorders();
        checkOrthoExclusiveSettings();
    }

    void Camera::setOrthographicProjection(float left, float right, float top, float botton) {
        _left = left;
        _right = right;
        _top = top;
        _botton = botton;

        checkOrthoExclusiveSettings();
    }

    void Camera::setLeft(float left) {
        _left = left;
        checkLeftRight();
    }

    void Camera::setRight(float right) {
        _right = right;
        checkLeftRight();
    }

    void Camera::setBotton(float botton) {
        _botton = botton;
        checkTopBotton();
    }

    void Camera::setTop(float top) {
        _top = top;
        checkTopBotton();
    }
//GETTERS
    bool Camera::getProjType() const { return _perspProj; }

    float Camera::getZnear() const { return _zNear; }
    float Camera::getZfar() const { return _zFar; }
    //PERSP
    float Camera::getAngle() const { return _angle; }
    float Camera::getScope() const { return _scope; }
    //ORTHO
    float Camera::getLeft() const { return _left; }
    float Camera::getRight() const { return _right; }
    float Camera::getBotton() const { return _botton; }
    float Camera::getTop() const { return _top; }
//-------
//MOVEMENTS
    void Camera::tilt(float angle) {
        //Calculamos matriz de transformacion
        glm::mat4 transform = glm::translate(_position) *
                glm::rotate(glm::radians(angle), glm::normalize(glm::cross(_upVec, _position - _target))) *
                glm::translate(-_position);
        //Rotamos el punto de mira y el vector UP
        _target = transform * glm::vec4(_target, 1.0f);
        _upVec = transform * glm::vec4(_upVec, 0.0f);
    }

    void Camera::pan(float angle) {
        //Calculamos matriz de transformacion
        glm::mat4 transform = glm::translate(_position) *
                glm::rotate(glm::radians(angle), _upVec) *
                glm::translate(-_position);
        //Rotamos el punto de mira y el vector UP
        _target = transform * glm::vec4(_target, 1.0f);
    }

    void Camera::dolly(float xMovement, float zMovement) {
        _target.x += xMovement;
        _target.z += zMovement;
        _position.x += xMovement;
        _position.z += zMovement;
    }

    void Camera::orbit(float xAngle, float yAngle) {
        glm::mat4 transform = glm::translate(_target) *
                            glm::rotate(glm::radians(xAngle), _upVec) *
                            glm::rotate(glm::radians(yAngle), glm::normalize(glm::cross(_upVec, _position - _target))) *
                            glm::translate(-_target);

        _position = transform * glm::vec4(_position, 1.0f);
        _upVec = transform * glm::vec4(_upVec, 0.0f);
    }

    void Camera::crane(float yMovement) {
        _target.y += yMovement;
        _position.y += yMovement;
    }

    void Camera::zoom(float value) {
        (_perspProj) ? zoomPersp(value) : zoomOrtho(value);
    }

    void Camera::zoomOrtho(float offset) {
        _left -= offset;
        _right += offset;
        _botton -= offset;
        _top += offset;
        checkOrthoExclusiveSettings();
    }

    void Camera::zoomPersp(float angle) {
        _angle += angle;
        checkAngle();
    }

} // PAG