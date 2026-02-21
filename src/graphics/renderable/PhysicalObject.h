#pragma once

#include "Mesh.h"
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class PhysicalObject {

	public:
		PhysicalObject(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		~PhysicalObject();
		void addMesh(Mesh* toAdd, string name);
		void computeModelMatrix();
		void render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor);
		tuple<string, float> selectNearestMesh(vec3 point, vec3 direction);
		string getName();
		map<string, Mesh*>* getMeshes();

	private:
		map<string, Mesh*> meshes;
		
		string name;
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
		mat4 modelMatrix;
};