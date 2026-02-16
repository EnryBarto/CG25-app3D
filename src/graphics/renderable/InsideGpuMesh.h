#pragma once

#include "../../libs.h"
#include "../../settings.h"
#include "../shader/Shader.h"
#include "MeshGeometry.h"

class InsideGpuMesh {

    public:
        void setModes(GLenum polygonMode, GLenum renderMode);
        void initVao(MeshGeometry* geometry);
        void setShader(Shader *shader);
        void render(mat4* modelMatrix, mat4* projectionMatrix, GLfloat currentTime, vec2 viewportResolution);

	private:
        const static uint8_t VERTICES_LAYER = 0;
        const static uint8_t COLORS_LAYER = 1;
        const static uint8_t NORMALS_LAYER = 2;
        const static uint8_t TEXTURE_LAYER = 3;

        unsigned int numIndexes, numVertices;

        // GPU buffers location
        GLuint vao = 0;     // Vertex Array Object (VAO) identifier
        GLuint vboVertices; // Vertex Buffer Object (VBO) identifier containing the object's vertex coordinates
        GLuint vboColors;   // VBO identifier containing the object's vertex colors
        GLuint vboNormals;  // VBO identifier containing the vertex normals
        GLuint vboTexture;  // VBO identifier containing the texture coordinates for the mesh vertices
        GLuint eboIndexes;  // Element Buffer Object (EBO) identifier

        GLenum polygonMode; // Drawing mode for vertex-to-polygon interpretation (ex. GL_FILL, GL_LINE, GL_POINT)
        GLenum drawMode;    // Vertex interpretation mode for the rendering stage (ex. GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_LINES, GL_POINTS)

        Shader* shader = 0;
        
        // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
        GLint uniform_Projection = -1;
        GLint uniform_Model = -1;
        GLint uniform_iTime = -1;
        GLint uniform_iResolution = -1;
};  