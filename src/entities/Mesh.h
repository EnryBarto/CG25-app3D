#pragma once

#include <utility>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "BoundingBox.h"
#include "../shader/Shader.h"
#include "../lighting/Material.h"
#include "../lighting/PointLight.h"
#include "../geometry/MeshGeometry.h"
#include "../gpu_objects/RenderableObject.h"
#include "../texture/Texture.h"

class PhysicalObject; // Forward declaration to avoid circular dependency

class Mesh {

	friend class PhysicalObject; // Needs access to recompute bounding box if the mesh model matrix is changed

	public:
		Mesh(MeshGeometry* geometry, Shader* basicShader, Material* defaultMaterial, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector, Shader* boundingBoxShader, Texture* skybox);
		~Mesh();
		void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, const vector<PointLight*>* lights, bool showBoundingBox);
		float distanceFromAnchor(vec3 point, vec3 direction, mat4 worldModelMatrix);
		bool isColliding(vec3 position, const mat4& objectModelMatrix, const mat4& objectInvertedModelMatrix);

		// GETTERS
		RenderableObject* getGpuObject();
		pair<vec3, vec3> getBoundingBox();
		vec3 getTranslationVector();
		vec3 getRotationAxis();
		float getRotationAngle();
		vec3 getScaleVector();
		Shader* getCurrentShader();
		Material* getCurrentMaterial();
		Material* getFileLoadedMaterial();
		Material* getCustomMaterial();
		Texture* getCurrentTexture();
		Texture* getFileLoadedTexture();

		// SETTERS
		void setShader(Shader* shader);
		void setMaterial(Material* material);
		void setFileLoadedMaterial(Material* material);
		void setTexture(Texture* texture);
		void setFileLoadedTexture(Texture* texture);

	protected:
		// The mesh model matrix cannot be directly edited because we want to update the object model matrix as well to keep them consistent
		void updateModelMatrix(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);

	private:
		RenderableObject* gpuObject;
		MeshGeometry* geometry;
		Material* material;
		Material* fileLoadedMaterial = nullptr;
		Material* customMaterial;
		BoundingBox* boundingBox;
		Texture* fileLoaded = nullptr;

		mat4 modelMatrix;
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
};