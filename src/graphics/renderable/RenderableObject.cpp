#include "RenderableObject.h"

void RenderableObject::getUniforms() {
	this->uniform_Model = glGetUniformLocation(shader->getProgramId(), "Model");
	this->uniform_Projection = glGetUniformLocation(shader->getProgramId(), "Projection");
	this->uniform_View = glGetUniformLocation(shader->getProgramId(), "View");
	this->uniform_ViewPos = glGetUniformLocation(shader->getProgramId(), "ViewPos");
	this->uniform_Light = glGetUniformLocation(shader->getProgramId(), "light");
	this->uniform_Material = glGetUniformLocation(shader->getProgramId(), "material");
	this->uniform_Texture = glGetUniformLocation(shader->getProgramId(), "uTexture");
	this->uniform_UsingTexture = glGetUniformLocation(shader->getProgramId(), "uUseTexture");
}

void RenderableObject::render(mat4* modelMatrix, mat4* projectionMatrix, mat4* viewMatrix) {
	
	if (this->vao == 0) {
		cerr << "ATTENTION!!! VAO not initialized" << endl;
		return;
	}

	if (this->shader == 0) {
		cerr << "ATTENTION!!! Shader not set" << endl;
		return;
	}

	glUseProgram(this->shader->getProgramId());

	// TEXTURE ACTIVATION
	glActiveTexture(GL_TEXTURE0);
	if (this->texture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, this->texture->getProgramId());
		if (this->uniform_UsingTexture != -1) glUniform1i(this->uniform_UsingTexture, 1); // Use texture
		if (this->uniform_Texture != -1)	  glUniform1i(this->uniform_Texture, 0);	  // Read texture from texture unit 0
	} else {
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
		if (this->uniform_UsingTexture != -1) glUniform1i(this->uniform_UsingTexture, 0); // Don't use texture
	}

	// Check for uniform existence in the active shader; if present, update them
	if (this->uniform_Model != -1) glUniformMatrix4fv(this->uniform_Model, 1, GL_FALSE, value_ptr(*modelMatrix));
	if (this->uniform_Projection != -1) glUniformMatrix4fv(this->uniform_Projection, 1, GL_FALSE, value_ptr(*projectionMatrix));
	if (this->uniform_View != -1) glUniformMatrix4fv(this->uniform_View, 1, GL_FALSE, value_ptr(*viewMatrix));

	// TODO: Set all uniforms

	// RENDER!
	glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode);
	glBindVertexArray(this->vao);
	glDrawElements(this->drawMode, this->numIndexes, GL_UNSIGNED_INT, 0);
}