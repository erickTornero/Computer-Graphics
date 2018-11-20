# ifndef __LIGHTM__
# define __LIGHTM__

# include <GL/glew.h>
# include <glm/glm.hpp>

class Light{
public:
    Light(GLfloat red = 1.0f, GLfloat green = 1.0f, GLfloat blue = 1.0f, GLfloat aIntensity = 1.0f,
    GLfloat xDir = 0.0f, GLfloat yDir = 1.0f, GLfloat zDir = 0.0f, GLfloat dIntensity = 1.0f):colour(glm::vec3(red, green, blue)), ambientIntensity(aIntensity), direction(glm::vec3(xDir, yDir, zDir)), diffuseIntensity(dIntensity){}

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    ~Light();

private:
    // ** Ambient light
    glm::vec3 colour;
    GLfloat ambientIntensity;

    // ** For Difuse light
    glm::vec3 direction;
    GLfloat diffuseIntensity;
};

# endif