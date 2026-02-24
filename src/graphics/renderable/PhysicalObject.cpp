#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector, Shader* boundingBoxShader) {
	this->name = name;
	this->updateModelMatrix(translation, rotationAxis, angle, scaleVector);
	this->boundingBoxShader = boundingBoxShader;
}

PhysicalObject::~PhysicalObject() {
	for (auto m : this->meshes) delete m.second;
	delete this->boundingBox;
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
	this->computeGlobalBoundingBox();
}

void PhysicalObject::removeMesh(Mesh* toRemove) {
	for (auto [id, mesh] : this->meshes) {
		if (mesh == toRemove) {
			this->meshes.erase(id);
			break;
		}
	}
	this->computeGlobalBoundingBox();
}

void PhysicalObject::updateModelMatrix(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->translation = translation;
	this->rotationAxis = rotationAxis;
	this->angle = angle;
	this->scaleVector = scaleVector;
	this->modelMatrix = translate(mat4(1.0), this->translation);
	if (this->angle != 0 && this->rotationAxis != vec3(0)) this->modelMatrix = rotate(this->modelMatrix, radians(this->angle), normalize(this->rotationAxis));
	this->modelMatrix = scale(this->modelMatrix, this->scaleVector);
}

void PhysicalObject::render(const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, const vector<PointLight*>* lights, bool showBoundingBox) {
	for (auto m : this->meshes) {
		m.second->render(this->modelMatrix, viewMatrix, projectionMatrix, camPos, showAnchor, lights, showBoundingBox);
	}
	if (showBoundingBox) this->boundingBox->render(this->modelMatrix, viewMatrix, projectionMatrix, camPos);
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

vec3 PhysicalObject::getTranslationVector() {
	return this->translation;
}

vec3 PhysicalObject::getRotationAxis() {
	return this->rotationAxis;
}

float PhysicalObject::getRotationAngle() {
	return this->angle;
}

vec3 PhysicalObject::getScaleVector() {
	return this->scaleVector;
}

void PhysicalObject::setName(const char* newName) {
	this->name = newName;
}

void PhysicalObject::computeGlobalBoundingBox() {
    // Delete the old bounding box if it exists
    if (this->boundingBox != nullptr) {
        delete this->boundingBox;
        this->boundingBox = nullptr;
    }

	// Retrieve all the bounding boxes
	vector<pair<vec3, vec3>> meshBoxes;
	for (auto [name, mesh] : this->meshes) {
		meshBoxes.push_back(mesh->getBoundingBox());
	}

	this->boundingBox = new BoundingBox(meshBoxes, this->boundingBoxShader);
}

void PhysicalObject::updateMeshModelMatrix(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->meshes.at(name)->updateModelMatrix(translation, rotationAxis, angle, scaleVector);
	this->computeGlobalBoundingBox();
}
