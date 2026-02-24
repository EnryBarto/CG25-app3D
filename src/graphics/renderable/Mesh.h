#pragma once

#include "gpu_objects/RenderableObject.h"
#include "MeshGeometry.h"
#include "../shader/Shader.h"
#include "../lighting/Material.h"
#include "../lighting/PointLight.h"
#include "BoundingBox.h"

class Mesh {
	public:
		Mesh(MeshGeometry* geometry, Shader* basicShader, Material* defaultMaterial, vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector, Shader* boundingBoxShader);
		~Mesh();
		void updateModelMatrix(vec3 translation, vec3 rotationAxis, float angle, vec3 scaleVector);
		void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, const vector<PointLight*>* lights, bool showBoundingBox);
		float distanceFromAnchor(vec3 point, vec3 direction, mat4 worldModelMatrix);
		vec3 getTranslationVector();
		vec3 getRotationAxis();
		float getRotationAngle();
		vec3 getScaleVector();
		void setShader(Shader* shader);
		Shader* getCurrentShader();
		Material* getCurrentMaterial();
		void setMaterial(Material* material);
		void setFileLoadedMaterial(Material* material);
		Material* getFileLoadedMaterial();
		Material* getCustomMaterial();;
		Texture* getCurrentTexture();
		void setTexture(Texture* texture);
		pair<vec3, vec3> getBoundingBox();

	private:
		RenderableObject* gpuObject;
		MeshGeometry* geometry;
		Material* material;
		Material* fileLoadedMaterial = nullptr;
		Material* customMaterial;
		BoundingBox* boundingBox;

		mat4 modelMatrix;
		vec3 translation;
		vec3 scaleVector;
		float angle;
		vec3 rotationAxis;
};