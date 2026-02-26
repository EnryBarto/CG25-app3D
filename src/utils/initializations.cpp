#include "initializations.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

int init_gl_glfw() {

	if (!glfwInit()) return -1;

	// Set context and profile properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Enable double buffering
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	return 0;
}

/* Create a windowed mode window and its OpenGL context */
GLFWwindow* init_window_context_events() {

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    
    const GLFWvidmode* mode = glfwGetVideoMode(monitor); // Contains current monitor resolution

    int window_width = (int)(WIDTH_RESIZE_FACTOR * mode->width);
    int window_height = (int)(HEIGHT_RESIZE_FACTOR * mode->height);
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, WINDOW_NAME, NULL, NULL);

    if (!window) {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate();
        return NULL;
    }

    /* Creates the current context and associates it with window.
     * In OpenGL, a rendering context is a state machine that stores all the necessary
     * information and resources for graphics rendering.
     */
    glfwMakeContextCurrent(window);


    // Checks whether the GLAD library successfully loaded all required OpenGL function pointers.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

void init_callbacks(GLFWwindow* window) {

    // Reset mouse position before attaching callback
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, 0, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetDropCallback(window, dragdrop_callback);
}

void init_imgui(GLFWwindow* window) {

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    // Get ImGui IO object to configure options
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = FONT_RESIZE_FACTOR;
    io.IniFilename = NULL; // Deactivate ini file

    ImGui::StyleColorsDark(); // Set ImGUI dark theme

    // Initialize ImGui for GLFW and OpenGL 3.3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

std::map<std::string, Shader*>* init_shaders() {
    std::map<std::string, Shader*>* shaders = new std::map<std::string, Shader*>();
    shaders->insert({ BASIC_SHADER_NAME, new Shader(BASIC_SHADER_NAME, "basic_vertex_shader.glsl", "basic_fragment_shader.glsl") });
    shaders->insert({ GOURAUD_SHADER_NAME, new Shader(GOURAUD_SHADER_NAME, "interpolation_vertex_shader.glsl", "interpolation_fragment_shader.glsl") });
    shaders->insert({ PHONG_SHADER_NAME, new Shader(PHONG_SHADER_NAME, "phong_vertex_shader.glsl", "phong_fragment_shader.glsl") });
    shaders->insert({ REFLECTION_SHADER_NAME, new Shader(REFLECTION_SHADER_NAME, "reflection_vertex_shader.glsl", "reflection_fragment_shader.glsl") });
    shaders->insert({ WAVE_SHADER_NAME, new Shader(WAVE_SHADER_NAME, "wave_vertex_shader.glsl", "interpolation_fragment_shader.glsl") });
    return shaders;
}

std::map<std::string, Texture*>* init_textures() {
    std::map<std::string, Texture*>* textures = new std::map<std::string, Texture*>();
    textures->insert({ "Cement", new Texture("Cement", (std::string(TEXTURES_PATH) + std::string("grey_cement.jpg")).c_str())});
    textures->insert({ "Italian flag", new Texture("Italian flag", (std::string(TEXTURES_PATH) + std::string("italian_flag.jpg")).c_str())});
    textures->insert({ "Sea", new Texture("Sea", (std::string(TEXTURES_PATH) + std::string("sea.jpg")).c_str())});
    textures->insert({ "Mickey Mouse", new Texture("Mickey Mouse", (std::string(TEXTURES_PATH) + std::string("mickey_mouse.jpg")).c_str())});
    textures->insert({ "Brick Wall", new Texture("Brick Wall", (std::string(TEXTURES_PATH) + std::string("brick_wall.jpg")).c_str())});
    textures->insert({ "Steve", new Texture("Steve", (std::string(TEXTURES_PATH) + std::string("steve.jpg")).c_str()) });
    textures->insert({ "Horse", new Texture("Horse", (std::string(TEXTURES_PATH) + std::string("horse.jpg")).c_str()) });
    return textures;
}

std::map<std::string, Material*>* init_materials() {
    std::map<std::string, Material*>* materials = new std::map<std::string, Material*>();

    // No material
    glm::vec3 no_material_ambient = vec3(1);
    glm::vec3 no_material_diffuse = vec3(0);
    glm::vec3 no_material_specular = vec3(0);
    float no_material_shininess = 1;
    materials->insert({ NO_MATERIAL_NAME, new Material(NO_MATERIAL_NAME, no_material_ambient, no_material_diffuse, no_material_specular, no_material_shininess) });

    // Red plastic
    glm::vec3 red_plastic_ambient = { 0.1f, 0.0f, 0.0f };
    glm::vec3 red_plastic_diffuse = { 0.6f, 0.1f, 0.1f };
    glm::vec3 red_plastic_specular = { 0.7f, 0.6f, 0.6f };
    float red_plastic_shininess = 150.0f;
    materials->insert({ "Red Plastic", new Material("Red Plastic", red_plastic_ambient, red_plastic_diffuse, red_plastic_specular, red_plastic_shininess) });

    // Brass
    glm::vec3 brass_ambient = { 0.5f, 0.06f, 0.015f };
    glm::vec3 brass_diffuse = { 0.78f, 0.57f, 0.11f };
    glm::vec3 brass_specular = { 0.99f, 0.91f, 0.81f };
    float brass_shininess = 27.8f;
    materials->insert({ "Brass", new Material("Brass", brass_ambient, brass_diffuse, brass_specular, brass_shininess) });

    // Emerald
    glm::vec3 emerald_ambient = { 0.0215f, 0.04745f, 0.0215f };
    glm::vec3 emerald_diffuse = { 0.07568f, 0.61424f, 0.07568f };
    glm::vec3 emerald_specular = { 0.633f, 0.727811f, 0.633f };
    float emerald_shininess = 78.8f;
    materials->insert({ "Emerald", new Material("Emerald", emerald_ambient, emerald_diffuse, emerald_specular, emerald_shininess) });

    // Snow white
    glm::vec3 snow_white_ambient = { 0.2f, 0.2f, 0.2f };
    glm::vec3 snow_white_diffuse = { 0.95f, 0.96f, 0.98f };
    glm::vec3 snow_white_specular = { 0.8f, 0.8f, 0.8f };
    float snow_white_shininess = 1.78125f;
    materials->insert({ "Snow White", new Material("Snow White", snow_white_ambient, snow_white_diffuse, snow_white_specular, snow_white_shininess) });

    // Yellow
    glm::vec3 yellow_ambient = { 0.8f, 0.8f, 0.0f };
    glm::vec3 yellow_diffuse = { 1.0f, 1.0f, 0.6f };
    glm::vec3 yellow_specular = { 0.9f, 0.9f, 0.04f };
    float yellow_shininess = 1.78125f;
    materials->insert({ "Yellow", new Material("Yellow", yellow_ambient, yellow_diffuse, yellow_specular, yellow_shininess) });

    // Pink
    glm::vec3 pink_ambient = { 0.05f, 0.0f, 0.0f };
    glm::vec3 pink_diffuse = { 0.5f, 0.4f, 0.4f };
    glm::vec3 pink_specular = { 0.7f, 0.04f, 0.04f };
    float pink_shininess = 1.78125f;
    materials->insert({ "Pink", new Material("Pink", pink_ambient, pink_diffuse, pink_specular, pink_shininess) });

    // Brown
    glm::vec3 brown_ambient = { 0.19125f, 0.0735f, 0.0225f };
    glm::vec3 brown_diffuse = { 0.7038f, 0.27048f, 0.0828f };
    glm::vec3 brown_specular = { 0.256777f, 0.137622f, 0.086014f };
    float brown_shininess = 12.8f;
    materials->insert({ "Brown", new Material("Brown", brown_ambient, brown_diffuse, brown_specular, brown_shininess) });

    return materials;
}