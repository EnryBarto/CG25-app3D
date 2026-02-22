#pragma once

#include "../shader/Shader.h"
#include "PhysicalObject.h"
#include "MeshGeometryFactory.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

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
		PhysicalObject* createFromFile(const char* path);

	private:
		static void normalizeModel(vector<pair<MeshGeometry*, string>>& models);
		Shader* defaultShader;
};