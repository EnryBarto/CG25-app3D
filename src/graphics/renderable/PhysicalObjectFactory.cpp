#include "PhysicalObjectFactory.h"

PhysicalObjectFactory::PhysicalObjectFactory(Shader* defaultShader) {
	this->defaultShader = defaultShader;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCube() {
	PhysicalObject* toReturn = new PhysicalObject(vec3(0), vec3(0), 0, vec3(1));
	MeshGeometry* cubeGeometry = MeshGeometryFactory::createCube();
	Mesh* cube = new Mesh(cubeGeometry, this->defaultShader, vec3(0), vec3(0), 0, vec3(1));
	toReturn->addMesh(cube);
	return toReturn;
}