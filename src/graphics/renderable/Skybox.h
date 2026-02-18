#pragma once

#include "../../libs.h"
#include "../shader/Shader.h"
#include "RenderableBackground.h"
#include "MeshGeometryFactory.h"

class Skybox {
	public:
		Skybox(Shader* shader, string textureDirectory);
		void render(mat4* viewMatrix, mat4* projectionMatrix);

	private:
		RenderableBackground* gpuBuffer;
};