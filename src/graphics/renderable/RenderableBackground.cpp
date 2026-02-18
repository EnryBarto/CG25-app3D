#include "RenderableBackground.h"

void RenderableBackground::getUniforms() {
	this->uniform_View = glGetUniformLocation(shader->getProgramId(), "View");
    this->uniform_Projection = glGetUniformLocation(shader->getProgramId(), "Projection");
    this->uniform_Skybox = glGetUniformLocation(shader->getProgramId(), "skybox");
}

void RenderableBackground::render(mat4* viewMatrix, mat4* projectionMatrix) {

    if (this->vao == 0) {
        cerr << "ATTENTION!!! VAO not initialized" << endl;
        return;
    }

    if (this->shader == 0) {
        cerr << "ATTENTION!!! Shader not set" << endl;
        return;
    }

    if (this->texture == nullptr) {
        cerr << "ATTENTION!!! Cubemap texture not set" << endl;
        return;
    }

    glUseProgram(this->shader->getProgramId());
    glDepthMask(GL_FALSE); // Disable depth writing for skybox background

    // Texture unit configuration
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture->getProgramId());
    glUniform1i(this->uniform_Skybox, 0);

    // Uniform updates
    glUniformMatrix4fv(this->uniform_View, 1, GL_FALSE, value_ptr(*viewMatrix));
    glUniformMatrix4fv(this->uniform_Projection, 1, GL_FALSE, value_ptr(*projectionMatrix));

    // Rendering
    glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode);
    glBindVertexArray(this->vao);
    glDrawElements(this->drawMode, this->numIndexes, GL_UNSIGNED_INT, 0);

    // State recover
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}