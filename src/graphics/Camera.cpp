#include "Camera.h"

Camera::Camera(vec3 position, vec3 target, vec3 upVector) {
    this->position = vec3(position);
    this->target = vec3(target);
    this->upVector = normalize(vec3(upVector));
    this->direction = normalize(this->target - this->position);
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

mat4 Camera::getViewMatrix() {
    return mat4(this->viewMatrix);
}

void Camera::moveForward(float deltaTime) {
    // Move forward along the normalized viewing direction
    vec3 dir = normalize(this->direction);
    this->move(dir * CAMERA_SPEED * deltaTime);
}

void Camera::moveBack(float deltaTime) {
    // Move the camera backward along the opposite direction
    vec3 dir = normalize(this->direction);
    this->move(dir * -CAMERA_SPEED * deltaTime);
}

void Camera::moveLeft(float deltaTime) {
    // Compute a vector perpendicular to the viewing direction and the camera's up vector (lateral slide)
    vec3 right = normalize(cross(this->direction, this->upVector));
    vec3 left = -right;
    this->move(left * CAMERA_SPEED * deltaTime);
}

void Camera::moveRight(float deltaTime) {
    // Move to the right relative to the camera's current orientation
    vec3 right = normalize(cross(this->direction, this->upVector));
    this->move(right * CAMERA_SPEED * deltaTime);
}

void Camera::moveUp(float deltaTime) {
    // Move along the camera's up vector (normalized)
    vec3 up = normalize(this->upVector);
    this->move(up * CAMERA_SPEED * deltaTime);
}

void Camera::moveDown(float deltaTime) {
    // Move down along the camera's up vector (negative direction)
    vec3 up = normalize(this->upVector);
    this->move(up * -CAMERA_SPEED * deltaTime);
}

void Camera::move(vec3 vector) {
    // Apply translation to both position and target, then update direction and view matrix
    this->position += vector;
    this->target += vector;
    this->direction = normalize(this->target - this->position);
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}