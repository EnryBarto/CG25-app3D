#pragma once

#include "../libs.h"
#include "../settings.h"
#include "Projection.h"

class Camera {
    
    public:
        Camera(vec3 position, vec3 target);
        void changeDirection(float xAxisRotation, float yAxisRotation);
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        const mat4& getViewMatrix();
        const vec3& getPosition();

	private:
        vec3 position;  // Camera position in 3D space
        vec3 target;    // Point the camera is looking at
        vec3 upVector;  // Up direction vector for the camera
        vec3 direction; // Viewing direction vector of the camera
        float xAxisAngle; // Pitch in degrees
        float yAxisAngle; // Yaw in degrees

        mat4 viewMatrix;

        void move(vec3 vector);
};