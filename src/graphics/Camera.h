#pragma once

#include "../libs.h"
#include "../settings.h"
#include "Projection.h"

class Camera {
    
    public:
        Camera(vec3 position, vec3 target, float speed);
        void rotateAroundCameraTarget(vec3 rotation, float angle);
        void changeDirection(float xAxisRotation, float yAxisRotation);
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        void setSpeed(float newSpeed);
        void undoLastOperation();
        const mat4& getViewMatrix();
        const vec3& getPosition();

	private:
        vec3 position;  // Camera position in 3D space
        vec3 target;    // Point the camera is looking at
        vec3 upVector;  // Up direction vector for the camera
        float speed;

        // Stored to undo the last camera movement: remember to call savestate()
        vec3 oldPosition;
        vec3 oldTarget;
        vec3 oldUpVector;

        mat4 viewMatrix; // Buffered view matrix to not recompute it for each frame, but it has to be kept updated

        void move(vec3 vector);
        void saveState();
};