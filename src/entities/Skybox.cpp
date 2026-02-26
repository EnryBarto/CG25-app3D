#include "Skybox.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glad/glad.h>

#include "../texture/Texture.h"
#include "../geometry/MeshGeometryFactory.h"
#include "../gpu_objects/RenderableBackground.h"

using namespace glm;

Skybox::Skybox(Shader* shader, string textureDirectory) {

	vector<string> faces{
		textureDirectory + "posx.jpg",
		textureDirectory + "negx.jpg",
		textureDirectory + "posy.jpg",
		textureDirectory + "negy.jpg",
		textureDirectory + "posz.jpg",
		textureDirectory + "negz.jpg"
	};

	this->gpuBuffer = new RenderableBackground();
	this->gpuBuffer->initVao(MeshGeometryFactory::createCube(vec4(1)));
	this->gpuBuffer->setShader(shader);
	this->gpuBuffer->setTexture(new Texture("Cubemap", faces));
	this->gpuBuffer->setModes(GL_TRIANGLES);
}

Skybox::~Skybox() {
	delete this->gpuBuffer;
}

void Skybox::render(const mat4& viewMatrix, const mat4& projectionMatrix) {
	this->gpuBuffer->render(viewMatrix, projectionMatrix);
}
