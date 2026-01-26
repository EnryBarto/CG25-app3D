#include "initializations.h"

GLFWwindow* initialize_all() {
    
	if (init_gl_glfw() != 0) {
		std::cout << "Glfw initialization failed!" << std::endl;
		return NULL;
	}

    GLFWwindow* window = init_window_context_events();

    if (window == NULL) {
        std::cout << "Failed creating the window and it's context!" << std::endl;
        return NULL;
    }

    init_callbacks(window);
    
    // Enable transparency management and depth test
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    init_imgui(window);

	return window;
}

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
}

void init_imgui(GLFWwindow* window) {

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    // Get ImGui IO object to configure options
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = FONT_RESIZE_FACTOR;

    ImGui::StyleColorsDark(); // Set ImGUI dark theme

    // Initialize ImGui for GLFW and OpenGL 3.3
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}
