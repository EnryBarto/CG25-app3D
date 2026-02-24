#pragma once

#include "Mesh.h"
#include <vector>
#include <map>
#include <tuple>
#include "../lighting/PointLight.h"
#include "BoundingBox.h"

using namespace std;

class PhysicalObject {

	public:
		PhysicalObject(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector, Shader* boundingBoxShader);
		~PhysicalObject();
		void addMesh(Mesh* toAdd, string name);
		void removeMesh(Mesh* toRemove);
		void updateModelMatrix(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		void render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, const vector<PointLight*>* lights, bool showBoundingBox);
		tuple<string, float> selectNearestMesh(vec3 point, vec3 direction);
		string getName();
		map<string, Mesh*>* getMeshes();
		vec3 getTranslationVector();
		vec3 getRotationAxis();
		float getRotationAngle();
		vec3 getScaleVector();
		void setName(const char* newName);
		void computeGlobalBoundingBox();
		void updateMeshModelMatrix(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		bool isColliding(vec3 position);

	private:
		map<string, Mesh*> meshes;
		BoundingBox* boundingBox = nullptr;

		string name;
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
		mat4 modelMatrix;
		Shader* boundingBoxShader;
		bool isCollidingWithExternalBoundingBox(vec3 position);
};