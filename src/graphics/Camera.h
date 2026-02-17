#include "../libs.h"
#include "../settings.h"
#include "Projection.h"

class Camera {
    
    public:
        Camera(int screenWidth, int screenHeight);
        Camera(vec3 position, vec3 target, vec3 upVector, int screenWidth, int screenHeight);
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);
        mat4 getViewMatrix();
        mat4 getProjectionMatrix();

	private:
        vec3 position;  // Camera position in 3D space
        vec3 target;    // Point the camera is looking at
        vec3 upVector;  // Up direction vector for the camera
        vec3 direction; // Viewing direction vector of the camera
        Projection* projection;

        mat4 viewMatrix;

        void move(vec3 vector);
};