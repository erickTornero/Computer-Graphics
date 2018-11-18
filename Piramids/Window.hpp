#ifndef __WINDOWM__
#define __WINDOWM__

# include <stdio.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

class Window{
public:
    Window(GLint wWidth = 800, GLint wHeight = 600):width(wWidth), height(wHeight){};
    int Initialize(const char *);

    GLint getBufferWidth(){return this->bufferWidth;}
    GLint getBufferHeight(){return this->bufferHeight;}
    
    bool getShouldClose() {return glfwWindowShouldClose(this->mainWindow);}

    void swapBuffers() {glfwSwapBuffers(this->mainWindow);}

    ~Window();
private:
    GLFWwindow * mainWindow;

    GLint width, height;
    GLint bufferWidth, bufferHeight;
};
#endif