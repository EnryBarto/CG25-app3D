#ifndef __SETTINGS_H
#define __SETTINGS_H

#define WINDOW_NAME "Bartocetti Enrico - App 3D"
#define WIDTH_RESIZE_FACTOR 0.8f
#define HEIGHT_RESIZE_FACTOR 0.8f
#define FONT_RESIZE_FACTOR 2.0f
#define MAX_FPS 100
#define SKYBOX_CUBEMAP_DIRECTORY "resources/skyboxes/clouds/"

// CAMERA AND PROJECTION SETTINGS
#define CAMERA_SPEED 1.5f
#define PROJ_FOVY 45.0f
#define PROJ_FARPLANE 2000.0f
#define PROJ_NEARPLANE 0.1f

// SHADERS
#define SHADER_FOLDER "resources/shaders/"
#define BASIC_SHADER_NAME "Basic"
#define PHONG_SHADER_NAME "Phong"
#define CUBEMAP_SHADER_NAME "Cubemap"
#define REFLECTION_SHADER_NAME "Reflection"
#define WAVE_SHADER_NAME "Wave"

#endif