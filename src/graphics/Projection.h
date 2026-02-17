#pragma once

#include "../libs.h"
#include "../settings.h"

class Projection {

	public:
        Projection(int width, int height);
        mat4 getProjectionMatrix();

	private:
        float fovY;         // Vertical field of view in degrees
        float aspectRatio;  // Aspect ratio (width/height) of the viewport
        float nearPlane;    // Distance to the near clipping plane
        float farPlane;     // Distance to the far clipping plane
        mat4 matrix;
};