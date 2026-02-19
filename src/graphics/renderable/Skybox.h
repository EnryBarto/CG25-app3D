#pragma once

#include "../../libs.h"
#include "../shader/Shader.h"
#include "RenderableBackground.h"
#include "MeshGeometryFactory.h"

class Skybox {
	public:
		Skybox(Shader* shader, string textureDirectory);
		void render(const mat4& viewMatrix, const mat4& projectionMatrix);

	private:
		RenderableBackground* gpuBuffer;
};