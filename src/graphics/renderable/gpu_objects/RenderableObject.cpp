#include "RenderableObject.h"

void RenderableObject::getUniforms() {
	this->uniform_Model = glGetUniformLocation(shader->getProgramId(), "Model");
	this->uniform_Projection = glGetUniformLocation(shader->getProgramId(), "Projection");
	this->uniform_View = glGetUniformLocation(shader->getProgramId(), "View");
	this->uniform_ViewPos = glGetUniformLocation(shader->getProgramId(), "ViewPos");
	this->uniform_NumLights = glGetUniformLocation(shader->getProgramId(), "numLights");
	for (int i = 0; i < MAX_LIGHTS; i++) {
		string base = "lights[" + to_string(i) + "].";
		this->uniform_LightPosition[i] = glGetUniformLocation(shader->getProgramId(), (base + "position").c_str());
		this->uniform_LightColor[i] = glGetUniformLocation(shader->getProgramId(), (base + "color").c_str());
		this->uniform_LightPower[i] = glGetUniformLocation(shader->getProgramId(), (base + "power").c_str());
	}
	this->uniform_MaterialAmbient = glGetUniformLocation(shader->getProgramId(), "material.ambient");
	this->uniform_MaterialDiffuse = glGetUniformLocation(shader->getProgramId(), "material.diffuse");
	this->uniform_MaterialSpecular = glGetUniformLocation(shader->getProgramId(), "material.specular");
	this->uniform_MaterialShininess = glGetUniformLocation(shader->getProgramId(), "material.shininess");
	this->uniform_Texture = glGetUniformLocation(shader->getProgramId(), "uTexture");
	this->uniform_UsingTexture = glGetUniformLocation(shader->getProgramId(), "uUseTexture");
	this->uniform_Time = glGetUniformLocation(shader->getProgramId(), "time");
}

void RenderableObject::render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, Material* material, const vector<PointLight*>* lights) {
	
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
	if (this->uniform_Model != -1) glUniformMatrix4fv(this->uniform_Model, 1, GL_FALSE, value_ptr(modelMatrix));
	if (this->uniform_Projection != -1) glUniformMatrix4fv(this->uniform_Projection, 1, GL_FALSE, value_ptr(projectionMatrix));
	if (this->uniform_View != -1) glUniformMatrix4fv(this->uniform_View, 1, GL_FALSE, value_ptr(viewMatrix));
	if (this->uniform_ViewPos != -1) glUniform3f(this->uniform_ViewPos, camPos.x, camPos.y, camPos.z);
	if (this->uniform_MaterialAmbient != -1) glUniform3fv(this->uniform_MaterialAmbient, 1, glm::value_ptr(material->getAmbient()));
	if (this->uniform_MaterialDiffuse != -1) glUniform3fv(this->uniform_MaterialDiffuse, 1, glm::value_ptr(material->getDiffuse()));
	if (this->uniform_MaterialSpecular != -1) glUniform3fv(this->uniform_MaterialSpecular, 1, glm::value_ptr(material->getSpecular()));
	if (this->uniform_MaterialShininess != -1) glUniform1f(this->uniform_MaterialShininess, material->getShininess());
	if (this->uniform_NumLights != -1) glUniform1i(this->uniform_NumLights, (GLint)lights->size());
	for (int i = 0; i < std::min((int)lights->size(), MAX_LIGHTS); i++) {
		if (this->uniform_LightColor[i] != -1) glUniform3f(this->uniform_LightColor[i], lights->at(i)->getColor().x, lights->at(i)->getColor().y, lights->at(i)->getColor().z);
		if (this->uniform_LightPosition[i] != -1) glUniform3f(this->uniform_LightPosition[i], lights->at(i)->getPosition().x, lights->at(i)->getPosition().y, lights->at(i)->getPosition().z);
		if (this->uniform_LightPower[i] != -1) glUniform1f(this->uniform_LightPower[i], lights->at(i)->getPower());
	}
	if (this->uniform_Time != -1) glUniform1f(this->uniform_Time, (float)glfwGetTime());

	// RENDER!
	glBindVertexArray(this->vao);
	glDrawElements(this->drawMode, this->numIndexes, GL_UNSIGNED_INT, 0);

	if (showAnchor) {
		glPointSize(ANCHOR_SIZE);
		glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(this->numIndexes * sizeof(GLuint)));
	}
}