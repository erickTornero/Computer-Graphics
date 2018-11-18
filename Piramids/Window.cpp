# include "Window.hpp"


int Window::Initialize(const char * nameW = "My Window"){
    //Initialize GLFW
    if(!glfwInit()){
        printf("GLFW Initializing fails\n");
        glfwTerminate();
        return 1;
    }
    // Setup GLFW window properties
    // OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Gives an error if lower version of OpenGL is used
    // Core profile = No backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward Compability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //Create a windows
    this->mainWindow = glfwCreateWindow(this->width, this->height, nameW, NULL, NULL);
    // Get Buffer size information
    glfwGetFramebufferSize(this->mainWindow, &this->bufferWidth, &this->bufferHeight);

    // Set the context for GLEW to use
    glfwMakeContextCurrent(this->mainWindow);
}

Window::~Window(){
    if(this->mainWindow != nullptr){
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
    }
}