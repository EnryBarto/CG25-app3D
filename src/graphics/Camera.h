#include "../libs.h"
#include "../settings.h"

class Camera {
    
    public:
        Camera();
        Camera(vec3 position, vec3 target, vec3 upVector);
        mat4 getLookAtMatrix();
        void moveForward(float deltaTime);
        void moveBack(float deltaTime);
        void moveLeft(float deltaTime);
        void moveRight(float deltaTime);
        void moveUp(float deltaTime);
        void moveDown(float deltaTime);

	private:
        vec3 position;  // Camera position in 3D space
        vec3 target;    // Point the camera is looking at
        vec3 upVector;  // Up direction vector for the camera
        vec3 direction; // Viewing direction vector of the camera
        mat4 viewMatrix;

        void move(vec3 vector);
};