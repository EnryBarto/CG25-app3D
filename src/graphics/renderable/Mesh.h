#pragma once

#include "RenderableObject.h"
#include "MeshGeometry.h"
#include "../shader/Shader.h"

class Mesh {
	public:
		Mesh(MeshGeometry* geometry, Shader* basicShader, vec3 translation, vec3 rotationAxis, float angle, vec3 scale);
		void render(mat4* modelMatrix, mat4* viewMatrix, mat4* projectionMatrix, vec3* camPos);

	private:
		RenderableObject* gpuObject;
		MeshGeometry* geometry;

		mat4 getModelMatrix();
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
};