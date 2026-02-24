#pragma once
#include <glm/fwd.hpp>
#include <glm/ext/vector_float3.hpp>
#include "../renderable/gpu_objects/RenderablePointLight.h"

using namespace glm;

class PointLight {
	public:
		PointLight(Shader* shader);
		PointLight(vec3 position, vec3 color, float power, Shader* shader);
		~PointLight();
		vec3 getPosition();
		vec3 getColor();
		float getPower();
		void setPosition(vec3 newPos);
		void setColor(vec3 newColor);
		void setPower(float power);
		void render(const mat4& viewMatrix, const mat4& projectionMatrix);

	private:
		vec3 position;
		vec3 color;
		float power;
		mat4 modelMatrix;

		RenderablePointLight* gpuBuffer;

		void updateSphereColor();
};