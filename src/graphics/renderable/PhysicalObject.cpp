#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->name = name;
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scaleVector;
	this->computeModelMatrix();
}

PhysicalObject::~PhysicalObject() {
	for (auto m : this->meshes) delete m.second;
}

void PhysicalObject::addMesh(Mesh* toAdd, string name) {
	string finalName = name;
	int counter = 1;

	// Check for duplicate names and increment the counter
	while (this->meshes.find(finalName) != this->meshes.end()) {
		finalName = name + "#" + to_string(counter);
		counter++;
	}

	this->meshes[finalName] = toAdd;
}

void PhysicalObject::computeModelMatrix() {
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), this->rotationAxis);
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void PhysicalObject::render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor) {
	for (auto m : this->meshes) {
		m.second->render(this->modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor);
	}
}

tuple<string, float> PhysicalObject::selectNearestMesh(vec3 point, vec3 direction) {
	string selectedMesh = "";
	float minDist = std::numeric_limits<float>::max();
	for (auto m : this->meshes) {
		float dist = m.second->distanceFromAnchor(point, direction, this->modelMatrix); if (dist != -1 && dist < minDist) {
			minDist = dist;
			selectedMesh = m.first;
		}
	}
	return make_tuple(selectedMesh, minDist);
}

string PhysicalObject::getName() {
	return this->name;
}

map<string, Mesh*>* PhysicalObject::getMeshes() {
	return &this->meshes;
}
