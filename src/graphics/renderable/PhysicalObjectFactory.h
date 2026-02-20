#pragma once

#include "../shader/Shader.h"
#include "PhysicalObject.h"
#include "MeshGeometryFactory.h"

class PhysicalObjectFactory {
		
	public:
		PhysicalObjectFactory(Shader* defaultShader);
		PhysicalObject* createSimpleCube(vec3 spawnPoint);
		PhysicalObject* createSimpleSphere(vec3 spawnPoint);
		PhysicalObject* createSimpleTorus(vec3 spawnPoint);
		PhysicalObject* createSimpleCone(vec3 spawnPoint);
		PhysicalObject* createSimpleCylinder(vec3 spawnPoint);
		PhysicalObject* createBase();
		PhysicalObject* createHouse(vec3 spawnPoint);

	private:
		Shader* defaultShader;
};