#pragma once

#include "Mesh.h"
#include <vector>

using namespace std;

class PhysicalObject {

	public:
		PhysicalObject(vec3 translation, vec3 rotationAxis, float angle, vec3 scale);
		void addMesh(Mesh* toAdd);
		void render(mat4* viewMatrix, mat4* projectionMatrix, vec3* camPos);

	private:
		vector<Mesh*> meshes;
		
		mat4 getModelMatrix();
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
};