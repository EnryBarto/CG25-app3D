#pragma once

#include "GpuBuffers.h"

class RenderableBackground : public GpuBuffers {

    public:
        void render(const mat4& viewMatrix, const mat4& projectionMatrix);

    protected:
        void getUniforms() override;

    private:
        // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
        GLint uniform_Projection = -1;
        GLint uniform_View = -1;
        GLint uniform_Skybox = -1;
};