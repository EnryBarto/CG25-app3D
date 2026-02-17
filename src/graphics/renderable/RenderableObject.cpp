#include "RenderableObject.h"

void RenderableObject::getUniforms() {
	this->uniform_Model = glGetUniformLocation(shader->getProgramId(), "Model");
	this->uniform_Projection = glGetUniformLocation(shader->getProgramId(), "Projection");
	this->uniform_View = glGetUniformLocation(shader->getProgramId(), "View");
	this->uniform_ViewPos = glGetUniformLocation(shader->getProgramId(), "ViewPos");
	this->uniform_Light = glGetUniformLocation(shader->getProgramId(), "light");
	this->uniform_Material = glGetUniformLocation(shader->getProgramId(), "material");
}

void RenderableObject::render(mat4 *modelMatrix, mat4 *projectionMatrix, GLfloat currentTime, vec2 viewportResolution) {
	
	if (this->vao == 0) {
		cerr << "ATTENTION!!! VAO not initialized" << endl;
		return;
	}

	if (this->shader == 0) {
		cerr << "ATTENTION!!! Shader not set" << endl;
		return;
	}

	glUseProgram(this->shader->getProgramId());
	
	// Check for uniform existence in the active shader; if present, update them
	if (this->uniform_Model != -1) glUniformMatrix4fv(this->uniform_Model, 1, GL_FALSE, value_ptr(*modelMatrix));

	if (this->uniform_Projection != -1) glUniformMatrix4fv(this->uniform_Projection, 1, GL_FALSE, value_ptr(*projectionMatrix));

	// TODO: Set all uniforms

	// RENDER!
	glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode);
	glBindVertexArray(this->vao);
	glDrawElements(this->drawMode, this->numIndexes, GL_UNSIGNED_INT, 0);
}