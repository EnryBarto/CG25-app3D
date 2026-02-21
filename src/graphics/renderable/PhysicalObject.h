#pragma once

#include "Mesh.h"
#include <vector>

using namespace std;

class PhysicalObject {

	public:
		PhysicalObject(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		~PhysicalObject();
		void addMesh(Mesh* toAdd);
		void computeModelMatrix();
		void render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor);

	private:
		vector<Mesh*> meshes;
		
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
		mat4 modelMatrix;
};