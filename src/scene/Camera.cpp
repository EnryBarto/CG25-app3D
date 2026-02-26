#include "Camera.h"

#include "../utils/constants.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(vec3 position, vec3 target, float speed) {
    this->setSpeed(speed);
    this->position = vec3(position);
    this->target = vec3(target);
    this->upVector = vec3(0, 1, 0);
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
    this->saveState();
}

const mat4& Camera::getViewMatrix() {
    return this->viewMatrix;
}

const vec3& Camera::getPosition() {
    return this->position;
}

void Camera::rotateAroundCameraTarget(vec3 axis, float angle) {
    if (glm::length(axis) == 0.0f) return; // Nothing to do

    this->saveState();

    // Relative vector from target to camera
    vec3 rel = this->position - this->target;

    // Rotate the relative vector around the normalized axis for the given angle
    axis = normalize(axis);
    vec3 rotated = vec3(glm::rotate(glm::mat4(1.0f), radians(-angle), axis) * vec4(rel, 0.0f));

    // New absolute position
    this->position = this->target + rotated;

    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

void Camera::changeDirection(float xAxisRotation, float yAxisRotation) {
    this->saveState();

    // Compute direction, pitch and yaw
    vec3 direction = normalize(this->target - this->position);
    float xAxisAngle = degrees(asin(clamp(direction.y, -1.0f, 1.0f))); // Use clamp to avoid NaN values (asin defined for [-1, 1]) because of float precision
    float yAxisAngle = degrees(atan2(direction.z, direction.x));

    // Update the rotation along the axes by the given offset
    yAxisAngle += yAxisRotation;
    xAxisAngle += xAxisRotation;

    // Let's make sure the camera doesn't flip
    if (xAxisAngle >  89.0f) xAxisAngle =  89.0f;
    if (xAxisAngle < -89.0f) xAxisAngle = -89.0f;

    // Calculate the x, y, and z coordinates of a point on the unit sphere, using the angles converted to radians.
    // This point represents the direction the camera is pointing.
    vec3 point;
    point.x = cos(radians(yAxisAngle)) * cos(radians(xAxisAngle));
    point.y = sin(radians(xAxisAngle));
    point.z = sin(radians(yAxisAngle)) * cos(radians(xAxisAngle));

    // Update the camera
    direction = normalize(point);
    this->target = this->position + direction;
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

void Camera::moveForward(float deltaTime) {
    // Move forward along the normalized viewing direction
    vec3 direction = normalize(this->target - this->position);
    this->move(direction * this->speed * deltaTime);
}

void Camera::moveBack(float deltaTime) {
    // Move the camera backward along the opposite direction
    vec3 direction = normalize(this->target - this->position);
    this->move(direction * -this->speed * deltaTime);
}

void Camera::moveLeft(float deltaTime) {
    // Compute a vector perpendicular to the viewing direction and the camera's up vector (lateral slide)
    vec3 direction = normalize(this->target - this->position);
    vec3 right = normalize(cross(direction, this->upVector));
    vec3 left = -right;
    this->move(left * this->speed * deltaTime);
}

void Camera::moveRight(float deltaTime) {
    // Move to the right relative to the camera's current orientation
    vec3 direction = normalize(this->target - this->position);
    vec3 right = normalize(cross(direction, this->upVector));
    this->move(right * this->speed * deltaTime);
}

void Camera::moveUp(float deltaTime) {
    // Move along the camera's up vector (normalized)
    vec3 up = normalize(this->upVector);
    this->move(up * this->speed * deltaTime);
}

void Camera::moveDown(float deltaTime) {
    // Move down along the camera's up vector (negative direction)
    vec3 up = normalize(this->upVector);
    this->move(up * -this->speed * deltaTime);
}

void Camera::setSpeed(float newSpeed) {
    if (newSpeed < CAMERA_SPEED_MIN) this->speed = CAMERA_SPEED_MIN;
    else if (newSpeed > CAMERA_SPEED_MAX) this->speed = CAMERA_SPEED_MAX;
    else this->speed = newSpeed;
}

void Camera::undoLastOperation() {
    // Recover last state, for example when there was a collision
    this->position = this->oldPosition;
    this->target = this->oldTarget;
    this->upVector = this->oldUpVector;
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

void Camera::move(vec3 vector) {
    this->saveState();
    // Apply translation to both position and target, then update direction and view matrix
    this->position += vector;
    this->target += vector;
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

void Camera::saveState() {
    this->oldPosition = this->position;
    this->oldTarget = this->target;
    this->oldUpVector = this->upVector;
}
