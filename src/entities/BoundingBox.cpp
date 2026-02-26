#include "BoundingBox.h"
#include "../geometry/MeshGeometryFactory.h"

BoundingBox::BoundingBox(MeshGeometry* geometry, Shader* basicShader, vec4 color) {
	this->min = vec3(std::numeric_limits<float>::max());
	this->max = vec3(-std::numeric_limits<float>::max());
	for (vec3 v : geometry->vertices) {
		this->min = glm::min(this->min, v);
		this->max = glm::max(this->max, v);
	}
	this->initGpuObject(basicShader, color);
	this->computeCorners();
}

BoundingBox::BoundingBox(const vector<pair<vec3, vec3>>& boundingBoxes, Shader* basicShader, vec4 color) {
	this->min = vec3(std::numeric_limits<float>::max());
	this->max = vec3(-std::numeric_limits<float>::max());
	for (const auto& bb : boundingBoxes) {
		this->min = glm::min(this->min, glm::min(bb.first, bb.second));
		this->max = glm::max(this->max, glm::max(bb.first, bb.second));
	}
	this->initGpuObject(basicShader, color);
	this->computeCorners();
}

BoundingBox::~BoundingBox() {
	delete this->gpuObject;
	delete this->geometry;
}

void BoundingBox::render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, vec3 camPos) {
	this->gpuObject->render(modelMatrix, viewMatrix, projectionMatrix, camPos, false, nullptr, nullptr);
}

vec3 BoundingBox::getMin() {
	return this->min;
}

vec3 BoundingBox::getMax() {
	return this->max;
}

const vector<vec3>& BoundingBox::getCorners() {
	return this->corners;
}

void BoundingBox::computeCorners() {
	this->corners.push_back(this->min);
	this->corners.push_back(vec3(this->min.x, this->min.y, this->max.z));
	this->corners.push_back(vec3(this->min.x, this->max.y, this->min.z));
	this->corners.push_back(vec3(this->min.x, this->max.y, this->max.z));
	this->corners.push_back(vec3(this->max.x, this->min.y, this->min.z));
	this->corners.push_back(vec3(this->max.x, this->min.y, this->max.z));
	this->corners.push_back(vec3(this->max.x, this->max.y, this->min.z));
	this->corners.push_back(this->max);
}

void BoundingBox::initGpuObject(Shader* basicShader, vec4 color) {
	this->geometry = MeshGeometryFactory::createBoundingBox(min, max, color);
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(this->geometry);
	this->gpuObject->setShader(basicShader);
	this->gpuObject->setModes(GL_LINE_STRIP);
}
