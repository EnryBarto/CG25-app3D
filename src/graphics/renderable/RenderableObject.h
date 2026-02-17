#pragma once

#include "GpuBuffers.h"

class RenderableObject: public GpuBuffers {

    public:
        void render(mat4* modelMatrix, mat4* projectionMatrix);

    protected:
        void getUniforms() override;

    private:
        // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
        GLint uniform_Projection = -1;
        GLint uniform_Model = -1;
        GLint uniform_View = -1;
        GLint uniform_ViewPos = -1;
        GLint uniform_Light = -1;
        GLint uniform_Material = -1;
        GLint uniform_Texture = -1;
        GLint uniform_UsingTexture = -1;
};  