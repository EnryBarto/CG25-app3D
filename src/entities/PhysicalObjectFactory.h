#pragma once

#include <vector>
#include <string>
#include <utility>
#include <glm/fwd.hpp>

#include "PhysicalObject.h"
#include "../geometry/MeshGeometry.h"
#include "../shader/Shader.h"
#include "../lighting/Material.h"

class PhysicalObjectFactory {
		
	public:
		PhysicalObjectFactory(Shader* defaultShader, Material* defaultMaterial, Shader* boundingBoxShader, Texture* skybox);
		PhysicalObject* createSimpleCube(vec3 spawnPoint);
		PhysicalObject* createSimpleSphere(vec3 spawnPoint);
		PhysicalObject* createSimpleTorus(vec3 spawnPoint);
		PhysicalObject* createSimpleCone(vec3 spawnPoint);
		PhysicalObject* createSimpleCylinder(vec3 spawnPoint);
		PhysicalObject* createBase();
		PhysicalObject* createHouse(vec3 spawnPoint);
		PhysicalObject* createFromFile(const char* path);

	private:
		static void normalizeModel(std::vector<std::pair<MeshGeometry*, std::string>>& models);
		Shader* defaultShader;
		Material* defaultMaterial;
		Shader* boundingBoxShader;
		Texture* skybox;
};