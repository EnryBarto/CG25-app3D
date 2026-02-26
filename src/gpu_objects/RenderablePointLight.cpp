#include "RenderablePointLight.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

void RenderablePointLight::getUniforms() {
	this->uniform_View = glGetUniformLocation(shader->getProgramId(), "View");
    this->uniform_Projection = glGetUniformLocation(shader->getProgramId(), "Projection");
    this->uniform_Model = glGetUniformLocation(shader->getProgramId(), "Model");
}

void RenderablePointLight::initVao(MeshGeometry* geometry) {

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

	// Add the anchor to the vertices and colors so it's copied into the VBO
	geometry->vertices.push_back(geometry->anchor);
	geometry->colors.push_back(geometry->anchorColor);
	
	// Generate the VAO and store the location
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	// Generates, activates and fills the vertices VBO
	glGenBuffers(1, &this->vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboVertices);
	glBufferData(GL_ARRAY_BUFFER, (this->numVertices + 1) * sizeof(vec3), geometry->vertices.data(), GL_STATIC_DRAW);

	// Loading the vertices VBO into layer 0
	glVertexAttribPointer(VERTICES_LAYER, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(VERTICES_LAYER);

	// Generates, activates and fills the colors VBO
	glGenBuffers(1, &this->vboColors);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
	glBufferData(GL_ARRAY_BUFFER, (this->numVertices + 1) * sizeof(vec4), geometry->colors.data(), GL_DYNAMIC_DRAW);

	// Loading the colors VBO into layer 1
	glVertexAttribPointer(COLORS_LAYER, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(COLORS_LAYER);

	// Generates, activates and fills the EBO
	glGenBuffers(1, &this->eboIndexes);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboIndexes);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->numIndexes + 1) * sizeof(GLuint), geometry->indexes.data(), GL_STATIC_DRAW);

	// VAO, VBO and EBO unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Restore the geometry after the anchor is copied
	geometry->vertices.pop_back();
	geometry->colors.pop_back();
	geometry->indexes.pop_back();
}

void RenderablePointLight::render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix) {

    if (this->vao == 0) {
        cerr << "ATTENTION!!! VAO not initialized" << endl;
        return;
    }

    if (this->shader == 0) {
        cerr << "ATTENTION!!! Shader not set" << endl;
        return;
    }

    glUseProgram(this->shader->getProgramId());

    // Uniform updates
    glUniformMatrix4fv(this->uniform_View, 1, GL_FALSE, value_ptr(viewMatrix));
    glUniformMatrix4fv(this->uniform_Projection, 1, GL_FALSE, value_ptr(projectionMatrix));
    glUniformMatrix4fv(this->uniform_Model, 1, GL_FALSE, value_ptr(modelMatrix));

    // Rendering
    glBindVertexArray(this->vao);
    glDrawElements(this->drawMode, this->numIndexes, GL_UNSIGNED_INT, 0);

    // State recover
    glBindVertexArray(0);
}

void RenderablePointLight::updateColor(vec3 lightColor) {
	vec4 color = vec4(lightColor, 1);
	vector<vec4> newColors(this->numVertices + 1, color);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboColors);
	glBufferSubData(GL_ARRAY_BUFFER, 0, newColors.size() * sizeof(vec4), newColors.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
