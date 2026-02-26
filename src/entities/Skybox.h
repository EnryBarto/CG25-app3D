#pragma once

#include <string>
#include <glm/fwd.hpp>

#include "../shader/Shader.h"
#include "../texture/Texture.h"
#include "../gpu_objects/RenderableBackground.h"

class Skybox {
	public:
		Skybox(Shader* shader, string textureDirectory);
        ~Skybox();
		void render(const mat4& viewMatrix, const mat4& projectionMatrix);
		Texture* getCubemapTexture();

	private:
		RenderableBackground* gpuBuffer;
		Texture* texture;
};