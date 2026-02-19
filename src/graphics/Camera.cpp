#include "Camera.h"

Camera::Camera(vec3 position, vec3 target, float speed) {
    this->setSpeed(speed);
    this->position = vec3(position);
    this->target = vec3(target);
    this->upVector = vec3(0, 1, 0);
    this->direction = normalize(this->target - this->position);
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);

    // Compute the pitch and the yaw
    this->xAxisAngle = degrees(asin(clamp(this->direction.y, -1.0f, 1.0f))); // Use clamp to avoid NaN values (asin defined for [-1, 1]) because of float precision
    this->yAxisAngle = degrees(atan2(this->direction.z, this->direction.x));
}

const mat4& Camera::getViewMatrix() {
    return this->viewMatrix;
}

const vec3& Camera::getPosition() {
    return this->position;
}

void Camera::changeDirection(float xAxisRotation, float yAxisRotation) {

    // Update the rotation along the axes by the given offset
    this->yAxisAngle += yAxisRotation;
    this->xAxisAngle += xAxisRotation;

    // Let's make sure the camera doesn't flip
    if (this->xAxisAngle >  89.0f) this->xAxisAngle =  89.0f;
    if (this->xAxisAngle < -89.0f) this->xAxisAngle = -89.0f;

    // Calculate the x, y, and z coordinates of a point on the unit sphere, using the angles converted to radians.
    // This point represents the direction the camera is pointing.
    vec3 point;
    point.x = cos(radians(this->yAxisAngle)) * cos(radians(this->xAxisAngle));
    point.y = sin(radians(this->xAxisAngle));
    point.z = sin(radians(this->yAxisAngle)) * cos(radians(this->xAxisAngle));

    // Update the camera
    this->direction = normalize(point);
    this->target = this->position + this->direction;
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}

void Camera::moveForward(float deltaTime) {
    // Move forward along the normalized viewing direction
    vec3 dir = normalize(this->direction);
    this->move(dir * this->speed * deltaTime);
}

void Camera::moveBack(float deltaTime) {
    // Move the camera backward along the opposite direction
    vec3 dir = normalize(this->direction);
    this->move(dir * -this->speed * deltaTime);
}

void Camera::moveLeft(float deltaTime) {
    // Compute a vector perpendicular to the viewing direction and the camera's up vector (lateral slide)
    vec3 right = normalize(cross(this->direction, this->upVector));
    vec3 left = -right;
    this->move(left * this->speed * deltaTime);
}

void Camera::moveRight(float deltaTime) {
    // Move to the right relative to the camera's current orientation
    vec3 right = normalize(cross(this->direction, this->upVector));
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

void Camera::move(vec3 vector) {
    // Apply translation to both position and target, then update direction and view matrix
    this->position += vector;
    this->target += vector;
    this->direction = normalize(this->target - this->position);
    this->viewMatrix = lookAt(this->position, this->target, this->upVector);
}