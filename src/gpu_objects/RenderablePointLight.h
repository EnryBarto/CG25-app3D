#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "GpuBuffers.h"
#include "../geometry/MeshGeometry.h"

using namespace glm;

class RenderablePointLight : public GpuBuffers {

    public:
        void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix);
        void updateColor(vec3 lightColor);
        void initVao(MeshGeometry* geometry) override;

    protected:
        void getUniforms() override;

    private:
        // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
        GLint uniform_Projection = -1;
        GLint uniform_View = -1;
        GLint uniform_Model = -1;
};