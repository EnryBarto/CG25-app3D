#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include "../gpu_objects/RenderablePointLight.h"
#include "../shader/Shader.h"

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