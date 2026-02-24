#pragma once
#include "MeshGeometry.h"
#include <glm/fwd.hpp>
#include "gpu_objects/RenderableObject.h"
#include "../shader/Shader.h"

class BoundingBox {

	public:
		BoundingBox(MeshGeometry* geometry, Shader* basicShader);
		BoundingBox(const vector<pair<vec3, vec3>>& boundingBoxes, Shader* basicShader); // Compute the bounding box of bounding boxes
		~BoundingBox();
		void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, vec3 camPos);
		vec3 getMin();
		vec3 getMax();

	private:
		vec3 max, min;
		MeshGeometry* geometry;
		RenderableObject* gpuObject;
};