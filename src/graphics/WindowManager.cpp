#include "WindowManager.h"

WindowManager::WindowManager() {
    this->lastWindowPosition[0] = 0;
    this->lastWindowPosition[1] = 0;
    this->lastWindowSize[0] = 0;
    this->lastWindowSize[1] = 0;
    this->_fullScreen = false;
    this->_frameBufferChanged = false;

    if (init_gl_glfw() != 0) {
        std::cout << "Glfw initialization failed!" << std::endl;
        throw exception();
    }

    this->window = init_window_context_events();

    if (this->window == NULL) {
        std::cout << "Failed creating the window and it's context!" << std::endl;
        throw exception();
    }

    init_callbacks(this->window);

    // Enable transparency management and depth test
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    // Set base color
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Set polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    init_imgui(this->window);
}

GLFWwindow* WindowManager::getWindow() {
    return this->window;
}

void WindowManager::frameBufferChanged() {
    // We want to use the full screen but mantaining the proportions
    vec2 res = this->getCurrentResolution();
    glViewport(0, 0, (int)res.x, (int)res.y);
    this->_frameBufferChanged = true;
}

bool WindowManager::isFrameBufferChanged() {
    bool tmp = this->_frameBufferChanged;
    this->_frameBufferChanged = false;
    return tmp;
}

bool WindowManager::isFullScreen() {
    return this->_fullScreen;
}

float WindowManager::getAspectRatio() {
    vec2 res = this->getCurrentResolution();
    return res.x / res.y;
}

void WindowManager::toggleFullScreen() {
    if (_fullScreen) {
        // Restore last positioning
        glfwSetWindowMonitor(this->window, nullptr, lastWindowPosition[0], lastWindowPosition[1], lastWindowSize[0], lastWindowSize[1], GLFW_DONT_CARE);
    } else {
        // Backup old positioning
        glfwGetWindowPos(this->window, &lastWindowPosition[0], &lastWindowPosition[1]);
        glfwGetWindowSize(this->window, &lastWindowSize[0], &lastWindowSize[1]);
        
        // Select the monitor to use as fullscreen and get the 
        GLFWmonitor* currentMonitor = this->getCurrentMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);

        // Switch to full screen
        glfwSetWindowMonitor(this->window, currentMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    this->_fullScreen = !this->_fullScreen;
}

vec2 WindowManager::getCurrentResolution() {
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    return vec2(width, height);
}

GLFWmonitor* WindowManager::getCurrentMonitor() {
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap, bestoverlap;
    GLFWmonitor* bestmonitor;
    GLFWmonitor** monitors;
    const GLFWvidmode* mode;

    bestoverlap = 0;
    bestmonitor = NULL;

    glfwGetWindowPos(this->window, &wx, &wy);
    glfwGetWindowSize(this->window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);

    for (i = 0; i < nmonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            std::max(0, std::min(wx + ww, mx + mw) - std::max(wx, mx)) *
            std::max(0, std::min(wy + wh, my + mh) - std::max(wy, my));

        if (bestoverlap < overlap) {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor != NULL ? bestmonitor : glfwGetPrimaryMonitor();
}