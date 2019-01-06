#ifndef __MATERIALM__
#define __MATERIALM__
#include <GL/glew.h>

class Material{
public:
    Material();
    Material(GLfloat sIntensity, GLfloat shine);

    void UseMaterial(GLuint specularItensityLocation, GLuint shininessLocation);
    ~Material();

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};

#endif