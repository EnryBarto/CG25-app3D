#include "BoundingBox.h"
#include "MeshGeometryFactory.h"

BoundingBox::BoundingBox(MeshGeometry* geometry, Shader* basicShader) {
	this->min = vec3(std::numeric_limits<float>::max());
	this->max = vec3(-std::numeric_limits<float>::max());
	for (vec3 v : geometry->vertices) {
		this->min = glm::min(this->min, v);
		this->max = glm::max(this->max, v);
	}
	this->geometry = MeshGeometryFactory::createBoundingBox(min, max);
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(this->geometry);
	this->gpuObject->setShader(basicShader);
	this->gpuObject->setModes(GL_LINE_STRIP);
}

BoundingBox::BoundingBox(const vector<pair<vec3, vec3>>& boundingBoxes, Shader* basicShader) {
	this->min = vec3(std::numeric_limits<float>::max());
	this->max = vec3(-std::numeric_limits<float>::max());
	for (const auto& bb : boundingBoxes) {
		this->min = glm::min(this->min, glm::min(bb.first, bb.second));
		this->max = glm::max(this->max, glm::max(bb.first, bb.second));
	}
	this->geometry = MeshGeometryFactory::createBoundingBox(min, max);
	this->gpuObject = new RenderableObject();
	this->gpuObject->initVao(this->geometry);
	this->gpuObject->setShader(basicShader);
	this->gpuObject->setModes(GL_LINE_STRIP);
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