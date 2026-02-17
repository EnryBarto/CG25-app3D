#include "GpuBuffers.h"

void GpuBuffers::setModes(GLenum polygonMode, GLenum renderMode) {
	this->polygonMode = polygonMode;
	this->drawMode = renderMode;
}

void GpuBuffers::initVao(MeshGeometry* geometry) {

	if (this->vao != 0) {
		cerr << "VAO already initialized" << endl;
		return;
	}

	if (geometry->getNumVertices() == 0) {
		cerr << "Can't create VAO without vertices" << endl;
		return;
	}

	this->numIndexes = geometry->getNumIndexes();
	this->numVertices = geometry->getNumVertices(); // Used to know also the number of colors, normals and texture coordinates

	// Generate the VAO and store the location
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	// Generates, activates and fills the vertices VBO
	glGenBuffers(1, &this->vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboVertices);
	glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(vec3), geometry->vertices.data(), GL_STATIC_DRAW);

	// Loading the vertices VBO into layer 0
	glVertexAttribPointer(VERTICES_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(VERTICES_LAYER);

	// Generates, activates and fills the colors VBO
	glGenBuffers(1, &this->vboColors);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
	glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(vec4), geometry->colors.data(), GL_STATIC_DRAW);

	// Loading the colors VBO into layer 1
	glVertexAttribPointer(COLORS_LAYER, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(COLORS_LAYER);

	// Generates, activates and fills the normals VBO (if provided)
	if (geometry->normals.size() == (size_t)this->numVertices) {
		glGenBuffers(1, &this->vboNormals);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboNormals);
		glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(vec3), geometry->normals.data(), GL_STATIC_DRAW);

		// Loading the normals VBO into layer 2
		glVertexAttribPointer(NORMALS_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(NORMALS_LAYER);
	}
	else {
		// No normals provided
		this->vboNormals = 0;
	}

	// Generates, activates and fills the texture VBO (if provided)
	if (geometry->textureCoordinates.size() == (size_t)this->numVertices) {
		glGenBuffers(1, &this->vboTexture);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboTexture);
		glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(vec2), geometry->textureCoordinates.data(), GL_STATIC_DRAW);

		// Loading the texture VBO into layer 3
		glVertexAttribPointer(TEXTURE_LAYER, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(TEXTURE_LAYER);
	}
	else {
		// No texture coordinates provided
		this->vboTexture = 0;
	}

	// Generates, activates and fills the EBO
	glGenBuffers(1, &this->eboIndexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboIndexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndexes * sizeof(GLuint), geometry->indexes.data(), GL_STATIC_DRAW);

	// VAO, VBO and EBO unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GpuBuffers::setShader(Shader* shader) {
	this->shader = shader;
	this->getUniforms();
}

void GpuBuffers::setTexture(Texture* texture) {
	this->texture = texture;
}

void GpuBuffers::unsetTexture() {
	this->texture = nullptr;
}
