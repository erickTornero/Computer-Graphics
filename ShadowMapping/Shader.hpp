#ifndef __SHADERM__
#define __SHADERM__

# include <stdio.h>
# include <string.h>
# include <iostream>
# include <fstream>

#include <GL/glew.h>

class Shader{
public:
    Shader();

    void CreateFromString(const char * vertexCode, const char * fragmentCode);
    void CreateFromFile(const char * fileV, const char * fileF);
    GLint GetProjectionLocation();
    GLint GetModelLocation();
    GLint GetViewLocation();
    GLint GetIntensityLocation();
    GLint GetAmbientColourLocation();
    GLint GetDiffuseIntensityLocation();
    GLint GetDirectionLocation();

    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();

    void UseShader();
    
    ~Shader();
private:
    GLuint shaderID;
    GLint uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection, uniformEyePosition, 
            uniformSpecularIntensity, uniformShininess;
    void CompileShader(const char * vertexCode, const char * fragmentCode);
    void AddShader(GLuint theProgram, const char * shaderCode, GLenum shaderType);
    void ClearShader();
    std::string ReadFileShader(const char * fileLoc);
};
#endif