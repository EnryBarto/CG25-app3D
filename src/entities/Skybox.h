#pragma once

#include <string>
#include <glm/fwd.hpp>

#include "../shader/Shader.h"
#include "../gpu_objects/RenderableBackground.h"

class Skybox {
	public:
		Skybox(Shader* shader, string textureDirectory);
        ~Skybox();
		void render(const mat4& viewMatrix, const mat4& projectionMatrix);

	private:
		RenderableBackground* gpuBuffer;
};