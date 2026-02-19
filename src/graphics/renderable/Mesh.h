#pragma once

#include "RenderableObject.h"
#include "MeshGeometry.h"
#include "../shader/Shader.h"

class Mesh {
	public:
		Mesh(MeshGeometry* geometry, Shader* basicShader, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		void computeModelMatrix();
		void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos);

	private:
		RenderableObject* gpuObject;
		MeshGeometry* geometry;

		mat4 modelMatrix;
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
};