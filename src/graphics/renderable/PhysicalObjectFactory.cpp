#include "PhysicalObjectFactory.h"

PhysicalObjectFactory::PhysicalObjectFactory(Shader* defaultShader) {
	this->defaultShader = defaultShader;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCube() {
	PhysicalObject* toReturn = new PhysicalObject(vec3(0), vec3(0), 0, vec3(1));
	MeshGeometry* cubeGeometry = MeshGeometryFactory::createCube();
	Mesh* cube = new Mesh(cubeGeometry, this->defaultShader, vec3(0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(cube);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createBase() {
	PhysicalObject* toReturn = new PhysicalObject(vec3(0), vec3(0), 0, vec3(1));
	MeshGeometry* planeGeometry = MeshGeometryFactory::createPlane(vec4(0.196078f, 0.568627f, 0.658824f, 1));
	Mesh* cube = new Mesh(planeGeometry, this->defaultShader, vec3(0, -1, 0), vec3(0), 0, vec3(5000, 0, 5000));
	toReturn->addMesh(cube);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createHouse() {
	PhysicalObject* toReturn = new PhysicalObject(vec3(-5, 0, 2), vec3(0), 0, vec3(1));
	MeshGeometry* geometry = MeshGeometryFactory::createCube();
	Mesh* mesh = new Mesh(geometry, this->defaultShader, vec3(0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(mesh);
	geometry = MeshGeometryFactory::createPyramid();
	mesh = new Mesh(geometry, this->defaultShader, vec3(0, 1, 0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(mesh);
	return toReturn;
}