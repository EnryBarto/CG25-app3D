#pragma once
#include "MeshGeometry.h"
#include <glm/fwd.hpp>
#include "gpu_objects/RenderableObject.h"
#include "../shader/Shader.h"

class BoundingBox {

	public:
		BoundingBox(MeshGeometry* geometry, Shader* basicShader, vec4 color);
		BoundingBox(const vector<pair<vec3, vec3>>& boundingBoxes, Shader* basicShader, vec4 color); // Compute the bounding box of bounding boxes
		~BoundingBox();
		void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, vec3 camPos);
		vec3 getMin();
		vec3 getMax();
		const vector<vec3>& getCorners();

	private:
		vec3 max, min;
		vector<vec3> corners;
		MeshGeometry* geometry;
		RenderableObject* gpuObject;
		void computeCorners();
		void initGpuObject(Shader* basicShader, vec4 color);
};