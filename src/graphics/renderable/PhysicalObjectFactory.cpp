#include "PhysicalObjectFactory.h"

PhysicalObjectFactory::PhysicalObjectFactory(Shader* defaultShader) {
	this->defaultShader = defaultShader;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCube(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(0), 0, vec3(2));
	MeshGeometry* cubeGeometry = MeshGeometryFactory::createCube();
	Mesh* cube = new Mesh(cubeGeometry, this->defaultShader, vec3(0, 1, 0), vec3(0), 0, vec3(1));
	toReturn->addMesh(cube);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleSphere(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(0), 0, vec3(2));
	MeshGeometry* sphereGeometry = MeshGeometryFactory::createSphere(vec4(0.5f, 0.8f, 1, 1));
	Mesh* sphere = new Mesh(sphereGeometry, this->defaultShader, vec3(0, 1, 0), vec3(0), 0, vec3(1));
	toReturn->addMesh(sphere);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleTorus(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(0), 0, vec3(2));
	MeshGeometry* torusGeometry = MeshGeometryFactory::createTorus(vec4(0.9f, 0.2f, 0.7f, 1));
	Mesh* torus = new Mesh(torusGeometry, this->defaultShader, vec3(0, 0.5f, 0), vec3(0, 0, 0), 0, vec3(1));
	toReturn->addMesh(torus);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCone(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(1, 0, 0), 180, vec3(2));
	MeshGeometry* coneGeometry = MeshGeometryFactory::createCone(vec4(0.9f, 0.7f, 0.15f, 1));
	Mesh* cone = new Mesh(coneGeometry, this->defaultShader, vec3(0, -1, 0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(cone);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCylinder(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(0), 0, vec3(2));
	MeshGeometry* cylinderGeometry = MeshGeometryFactory::createCylinder(vec4(0.2f, 0.8f, 0.1f, 1));
	Mesh* cylinder = new Mesh(cylinderGeometry, this->defaultShader, vec3(0), vec3(0), 0, vec3(1));
	toReturn->addMesh(cylinder);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createBase() {
	PhysicalObject* toReturn = new PhysicalObject(vec3(0), vec3(0), 0, vec3(2));
	MeshGeometry* planeGeometry = MeshGeometryFactory::createPlane(vec4(0.196078f, 0.568627f, 0.658824f, 1));
	Mesh* cube = new Mesh(planeGeometry, this->defaultShader, vec3(0, 0, 0), vec3(0), 0, vec3(5000, 0, 5000));
	toReturn->addMesh(cube);
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createHouse(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject(spawnPoint, vec3(0), 0, vec3(2));
	MeshGeometry* geometry = MeshGeometryFactory::createCube();
	Mesh* mesh = new Mesh(geometry, this->defaultShader, vec3(0, 1, 0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(mesh);
	geometry = MeshGeometryFactory::createPyramid();
	mesh = new Mesh(geometry, this->defaultShader, vec3(0, 2, 0), vec3(0, 1, 0), 180, vec3(1));
	toReturn->addMesh(mesh);
	return toReturn;
}