#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#define WINDOW_NAME "Bartocetti Enrico - App 3D"
#define WIDTH_RESIZE_FACTOR 0.8f
#define HEIGHT_RESIZE_FACTOR 0.8f
#define FONT_RESIZE_FACTOR 2.0f
#define MAX_FPS 100
#define SKYBOX_CUBEMAP_DIRECTORY "resources/skyboxes/icebergs/"
#define ANCHOR_SIZE 15
#define ANCHOR_SPERE_RADIUS 0.5f
#define GUI_WINDOWS_PADDING 10
#define MAX_LENGTH_OBJ_NAME 25
#define NO_MATERIAL_NAME "No Material"
#define TEXTURES_PATH "resources/textures/"

// LIGHT SETTINGS
#define MAX_LIGHTS 10 // It's important to keep the costant updated also in the shader files
#define MAX_LIGHT_POWER 3.5f
#define MIN_LIGHT_POWER 0

// PROJECTION SETTINGS
#define PROJ_FOVY_DEFAULT 80.0f
#define PROJ_FOVY_MAX 115.0f
#define PROJ_FOVY_MIN 45.0f
#define PROJ_FARPLANE 2000.0f
#define PROJ_NEARPLANE 0.1f

// CAMERA SETTINGS
#define CAMERA_SPEED_DEFAULT 8.0f
#define CAMERA_SPEED_MIN 1.5f
#define CAMERA_SPEED_MAX 40.0f
#define MOUSE_SENSITIVITY_DEFAULT 0.05f
#define MOUSE_SENSITIVITY_MIN 0.01f
#define MOUSE_SENSITIVITY_MAX 0.2f
#define TRACKBALL_SPEED_DEFAULT 20.0f
#define TRACKBALL_SPEED_MIN 5.0f
#define TRACKBALL_SPEED_MAX 50.0f
#define ARROW_KEY_CAMERA_SPEED_FACTOR 0.75f
#define CAMERA_COLLISION_RADIUS 0.5f

// SHADERS
#define SHADER_FOLDER "resources/shaders/"
#define BASIC_SHADER_NAME "Basic"
#define GOURAUD_SHADER_NAME "Gouraud"
#define PHONG_SHADER_NAME "Phong"
#define CUBEMAP_SHADER_NAME "Cubemap"
#define REFLECTION_SHADER_NAME "Reflection"
#define WAVE_SHADER_NAME "Wave"

#endif