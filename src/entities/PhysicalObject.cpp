#include "PhysicalObject.h"

#include <glm/gtc/matrix_transform.hpp>

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
	while (this->angle >= 360) this->angle -= 360;
	while (this->angle < 0) this->angle += 360;
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

	this->boundingBox = new BoundingBox(meshBoxes, this->boundingBoxShader, vec4(1, 0, 1, 1));
}

void PhysicalObject::updateMeshModelMatrix(string name, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector) {
	this->meshes.at(name)->updateModelMatrix(translation, rotationAxis, angle, scaleVector);
	this->computeGlobalBoundingBox();
}

bool PhysicalObject::isColliding(vec3 position) {
	// Firstly we check if there is collision with the external bounding box
	if (isCollidingWithExternalBoundingBox(position)) {
		// If there is collision we check the collision with all the mesh of the objects
		mat4 inverseModelMatrix = glm::inverse(this->modelMatrix); // Used to improve performance
		for (auto [t, m] : this->meshes) {
			if (m->isColliding(position, this->modelMatrix, inverseModelMatrix)) return true;
		}
		return false;
	} else {
		// If there isn't collision with the external bounding box we immediately skip the test
		return false;
	}
}

bool PhysicalObject::isCollidingWithExternalBoundingBox(vec3 position) {
	// Because the object can be rotated or not uniformly scaled (Oriented Bounding Box), we find ne nearest point in OCS
	// (where the bounding box is axis aligned), and then take it back to WCS

	// Camera position in OCS
	vec3 localPos = vec3(glm::inverse(this->modelMatrix) * vec4(position, 1));

	// Original bounding box extremes
	vec3 boundingMin = this->boundingBox->getMin();
	vec3 boundingMax = this->boundingBox->getMax();
	vec3 nearestPointLocal = glm::max(boundingMin, glm::min(localPos, boundingMax)); // Clamping: Point of the object nearest to the sphere in OCS

	// Take back the nearest point to WCS
	vec3 nearestPointWorld = vec3(this->modelMatrix * vec4(nearestPointLocal, 1));

	vec3 difference = nearestPointWorld - position; // Distance from the center of the spere to the nearest point on the bounding box

	// Instead of calculating the distance, we consider the squared distance to avoid numerical problems because of the square root
	return glm::dot(difference, difference) <= (CAMERA_COLLISION_RADIUS * CAMERA_COLLISION_RADIUS);
}