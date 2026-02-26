#pragma once

#include "GpuBuffers.h"
#include "../../lighting/Material.h"
#include "../../lighting/PointLight.h"
#include "../../../settings.h"
#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class RenderableObject: public GpuBuffers {

    public:
        void render(const mat4& modelMatrix, const mat4& viewMatrix, const mat4& projectionMatrix, const vec3& camPos, bool showAnchor, Material* material, const vector<PointLight*>* lights);
        bool canUseBlinnPhong();
        void setBlinnPhong(bool flag);
        bool isUsingBlinnPhong();
		bool supportsTexture();
		bool supportsMaterial();

    protected:
        void getUniforms() override;

    private:
        // Cached handles to shader uniform variables to avoid repeated lookups, -1 if not used by the shader
        GLint uniform_Projection = -1;
        GLint uniform_Model = -1;
        GLint uniform_View = -1;
        GLint uniform_ViewPos = -1;
        GLint uniform_NumLights = -1;
        GLint uniform_LightPosition[MAX_LIGHTS];
        GLint uniform_LightColor[MAX_LIGHTS];
        GLint uniform_LightPower[MAX_LIGHTS];
        GLint uniform_MaterialAmbient = -1;
        GLint uniform_MaterialDiffuse = -1;
        GLint uniform_MaterialSpecular = -1;
        GLint uniform_MaterialShininess = -1;
        GLint uniform_Texture = -1;
        GLint uniform_UsingTexture = -1;
        GLint uniform_Time = -1;
        GLint uniform_UsingBlinnPhong = -1;

        bool usingBlinnPhong = false;
};  