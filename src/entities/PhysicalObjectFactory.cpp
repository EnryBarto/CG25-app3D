#include "PhysicalObjectFactory.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "../geometry/MeshGeometryFactory.h"

using namespace std;
using namespace glm;

PhysicalObjectFactory::PhysicalObjectFactory(Shader* defaultShader, Material* defaultMaterial, Shader* boundingBoxShader, Texture *skybox) {
	this->defaultShader = defaultShader;
	this->defaultMaterial = defaultMaterial;
	this->boundingBoxShader = boundingBoxShader;
	this->skybox = skybox;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCube(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("Simple Cube", spawnPoint, vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* cubeGeometry = MeshGeometryFactory::createCube(vec4(0.196078f, 0.568627f, 0.658824f, 1));
    Mesh* cube = new Mesh(cubeGeometry, this->defaultShader, this->defaultMaterial, vec3(0, 1, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(cube, "Cube");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleSphere(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("Simple sphere", spawnPoint, vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* sphereGeometry = MeshGeometryFactory::createSphere(vec4(0.5f, 0.8f, 1, 1));
    Mesh* sphere = new Mesh(sphereGeometry, this->defaultShader, this->defaultMaterial, vec3(0, 1, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(sphere, "Sphere");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleTorus(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("Simple torus", spawnPoint, vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* torusGeometry = MeshGeometryFactory::createTorus(vec4(0.9f, 0.2f, 0.7f, 1));
    Mesh* torus = new Mesh(torusGeometry, this->defaultShader, this->defaultMaterial, vec3(0, 0.5f, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(torus, "Torus");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCone(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("Simple cone", spawnPoint, vec3(1, 0, 0), 180, vec3(2), this->boundingBoxShader);
	MeshGeometry* coneGeometry = MeshGeometryFactory::createCone(vec4(0.9f, 0.7f, 0.15f, 1));
    Mesh* cone = new Mesh(coneGeometry, this->defaultShader, this->defaultMaterial, vec3(0, -1, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(cone, "Cone");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createSimpleCylinder(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("Simple cylinder", spawnPoint, vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* cylinderGeometry = MeshGeometryFactory::createCylinder(vec4(0.2f, 0.8f, 0.1f, 1));
    Mesh* cylinder = new Mesh(cylinderGeometry, this->defaultShader, this->defaultMaterial, vec3(0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(cylinder, "Cylinder");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createBase() {
	PhysicalObject* toReturn = new PhysicalObject("Floor", vec3(0), vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* planeGeometry = MeshGeometryFactory::createTriangulatedPlane(512, vec4(0.196078f, 0.568627f, 0.658824f, 1));
    Mesh* cube = new Mesh(planeGeometry, this->defaultShader, this->defaultMaterial, vec3(0, 0, 0), vec3(0), 0, vec3(1000, 1, 1000), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(cube, "Plane");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createHouse(vec3 spawnPoint) {
	PhysicalObject* toReturn = new PhysicalObject("House", spawnPoint, vec3(0), 0, vec3(2), this->boundingBoxShader);
	MeshGeometry* geometry = MeshGeometryFactory::createCube(vec4(0.196078f, 0.568627f, 0.658824f, 1));
    Mesh* mesh = new Mesh(geometry, this->defaultShader, this->defaultMaterial, vec3(0, 1, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(mesh, "Cube");
	geometry = MeshGeometryFactory::createPyramid(vec4(0.196078f, 0.568627f, 0.658824f, 1));
    mesh = new Mesh(geometry, this->defaultShader, this->defaultMaterial, vec3(0, 2, 0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
	toReturn->addMesh(mesh, "Pyramid");
	return toReturn;
}

PhysicalObject* PhysicalObjectFactory::createFromFile(const char* path) {
	vector<pair<MeshGeometry*, string>> models;
	map<MeshGeometry*, Material*> materials;
	cout << "+ Started loading " << path << endl;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene) {
		cerr << importer.GetErrorString() << endl;
		return nullptr;
	}

	PhysicalObject* toReturn = new PhysicalObject("File loaded", vec3(0), vec3(0), 0, vec3(1), this->boundingBoxShader);
	
	const aiMesh* assimpMesh;
	const aiMaterial* assimpMaterial;

	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		assimpMesh = scene->mMeshes[i];

		MeshGeometry* geometry = MeshGeometryFactory::createFromAssimpMesh(assimpMesh);
		if (geometry != nullptr) {
			models.push_back({geometry, assimpMesh->mName.C_Str() });
		}

		assimpMaterial = scene->mMaterials[assimpMesh->mMaterialIndex];
		Material* loadedMaterial = nullptr;
		try {
			loadedMaterial = new Material(assimpMaterial);
		} catch (const std::runtime_error& e) {
			cerr << "Warning: Material load failed for mesh " << assimpMesh->mName.C_Str() << ". Error: " << e.what() << ". Using default material." << endl;
			loadedMaterial = this->defaultMaterial;
		}
		materials.insert({geometry, loadedMaterial});
	}

	PhysicalObjectFactory::normalizeModel(models);

	for (auto [ geometry, name ] : models) {
		Material* material = materials.at(geometry);
        Mesh* mesh = new Mesh(geometry, this->defaultShader, material, vec3(0), vec3(0), 0, vec3(1), this->boundingBoxShader, this->skybox);
		if (material != this->defaultMaterial) mesh->setFileLoadedMaterial(material);
		toReturn->addMesh(mesh, name);
	}

	return toReturn;
}

void PhysicalObjectFactory::normalizeModel(vector<pair<MeshGeometry*, string>>& models) {
	unsigned int numMeshes = (unsigned int)models.size();
	vector<vec3> minimum, maximum;
	vec3 centroid = vec3(0);
	vec3 min, max;

	// Compute the centroid of the model (by averaging its vertices)
	unsigned int numVertices = 0;
	for (auto [mesh, name] : models) {
		for (vec3 vertex : mesh->vertices) {
			centroid += vertex;
			numVertices++;
		}
	}

	centroid /= (float)numVertices;

	for (auto [mesh, name] : models) {
		for (vec3& vertex : mesh->vertices) {
			vertex -= centroid;
		}
		mesh->anchor -= centroid;
	}

	// Find the minimum and maximum values for all model coordinates
	min = vec3(std::numeric_limits<float>::max());
	max = vec3(-std::numeric_limits<float>::max());

	for (auto [mesh, name] : models) {
		for (vec3 vertex : mesh->vertices) {
			min.x = std::min(min.x, vertex.x);
			max.x = std::max(max.x, vertex.x);
			min.y = std::min(min.y, vertex.y);
			max.y = std::max(max.y, vertex.y);
			min.z = std::min(min.z, vertex.z);
			max.z = std::max(max.z, vertex.z);
		}
	}

	// Compute the scale factor for each dimension (to preserve proportions)
	vec3 range = max - min;

	float maxRange = std::max({ range.x, range.y, range.z });

	if (maxRange == 0.0f) maxRange = 1.0f;
	for (auto [mesh, name] : models) {
		for (vec3& vertex : mesh->vertices) {
			vertex = 2.0f * (vertex - min) / maxRange - 1.0f;
		}
		mesh->anchor = 2.0f * (mesh->anchor - min) / maxRange - 1.0f;
	}
}
