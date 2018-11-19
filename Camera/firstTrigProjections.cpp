// This code is based on the course of Udemy
// Draw a piramed from four triangles.
# include <stdio.h>
# include <string.h>
# include <math.h>

# include <GL/glew.h>
# include <GLFW/glfw3.h>
//# define GLM_FORCE_CUDA
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Window.hpp"
# include <vector>
# include "Camera.hpp"

//# include <glm/mat4x4.hpp>
GLint uniformModel = 0, uniformProjection = 0, uniformView = 0;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;


const GLint WIDTH = 800, HEIGHT = 600;
const float toRandians = 3.14159265f/180.0f;
// VAO: Vertex Array Object
// VBO: Vertex Buffer Objectx
// IBO: Index Buffer Object
std::vector<Mesh*> objects;
bool direction = true;
bool directionY = true;
float triOffset = 0.0f;
float triOffsetY = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.00005f;
float triIncrementY = 0.00006;
float currAngle = 0.0f;
float curSZ = 0.1f;
bool dirSZ = true;
float maxSZ = 0.8;
float minSZ = 0.1;
// ** Location of same Shaders:
const char * vShaderLoc = "shaders/vertex.hlsl";
const char * fShaderLoc = "shaders/fragment.hlsl";
// * * Vertex Shader
static const char * vShader = "                         \n\
#version 330                                            \n\
                                                        \n\
layout (location = 0) in vec3 pos;                      \n\
                                                        \n\
out vec4 vCol;                                          \n\
                                                        \n\
uniform mat4 model;                                     \n\
uniform mat4 projection;                                \n\
                                                        \n\
void main(){                                            \n\
    //gl_Position = projection * model * vec4(pos.x, pos.y, pos.z,1.0);  \n\
    gl_Position = projection * model * vec4(pos,1.0);                \n\
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);          \n\
}";

// * Fragment shader
static const char *fShader =  "                         \n\
#version 330                                            \n\
                                                        \n\
in vec4 vCol;                                           \n\
                                                        \n\
out vec4 colour;                                        \n\
                                                        \n\
void main(){                                            \n\
    //colour = vec4(1.0,0.0,0.0,1.0);                   \n\
    colour = vCol;                                      \n\
}";

void CreateTriangle(){
    // Create a set of indexes, that specifies how to take each of the four triangles
    unsigned int indexes[] = {
        0, 3, 1,    //Define the first triangle
        1, 3, 2,
        0, 2, 3,
        0, 1, 2
    };
    // Four points can define a piramid in the 3D Space
    // So we define 4 vertex.
    GLfloat vertices[]={
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    Mesh *m = new Mesh();
    m->CreateMesh(vertices, indexes, 12, 12);
    objects.push_back(m);
}
int main(){
    Window * window = new Window();
    window->Initialize("Pirámides voladoras");
    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if(glewInit() != GLEW_OK){
        printf("GLEW initialisation Fails!!\n");
        delete window;
        return 1;
    }
    glEnable(GL_DEPTH_TEST);
    // Setup Viewport size
    GLint bufferWidth = window->getBufferWidth();
    GLint bufferHeight = window->getBufferHeight();
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    CreateTriangle();
    CreateTriangle();
    Shader * shader = new Shader();
    //shader->CreateFromString(vShader, fShader);
    shader->CreateFromFile(vShaderLoc, fShaderLoc);

    Camera * camera = new Camera(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f), -90.0f,0.0f, 5.0f, 0.3f);
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);
    // Loop until window closed
    while(!window->getShouldClose()){
        
        GLfloat now = glfwGetTime();    // * Return time in milliseconds
        deltaTime = now - lastTime;
        lastTime = now;

        // Get + Handle user input events: move mouse, press key
        glfwPollEvents();

        camera->KeyControl(window->getKeys(), deltaTime);
        camera->MouseControl(window->getXChange(), window->getYChange());
        if(direction){
            triOffset += triIncrement;
        }
        else{
            triOffset -= triIncrement;
        }
        if(abs(triOffset) >= triMaxoffset){
            direction = !direction;
        }
        currAngle += 0.01;
        if(currAngle >= 360){
            currAngle -= 360;
        }
        if(dirSZ){
            curSZ+=0.0001;
        }else{
            curSZ -=0.0001;
        }
        if(curSZ >= maxSZ or curSZ <= minSZ)
            dirSZ = !dirSZ;
        // Clear window
        // as arguments RGB, and alpha which is the transparent
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Clearing the color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->UseShader();
        //uniformModel = shader->GetModelLocation();
        //uniformProjection = shader->GetProjectionLocation();
        //uniformView = shader->GetViewLocation();
        glm::mat4 model(1.0f);
        // Rotate around the Z axis
        model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.5f));
        //model = glm::rotate(model, currAngle*toRandians, glm::vec3(0.0f, 0.8f, 0.0f));
        //model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));
        //Scalling:
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(shader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(shader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
        objects[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, -1.5f));
        model = glm::rotate(model, currAngle*toRandians, glm::vec3(0.0f, 0.8f, 0.0f));
        //model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));
        //Scalling:
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
        objects[1]->RenderMesh();
        

        glUseProgram(0);
        window->swapBuffers();
    }
    delete camera;
    delete window;
    delete shader;

    return 0;
}