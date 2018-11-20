# ifndef __LIGHTM__
# define __LIGHTM__

# include <GL/glew.h>
# include <glm/glm.hpp>

class Light{
public:
    Light(GLfloat red = 1.0f, GLfloat green = 1.0f, GLfloat blue = 1.0f, GLfloat aIntensity = 1.0f):colour(glm::vec3(red, green, blue)), ambientIntensity(aIntensity){}

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation);
    ~Light();

private:
    glm::vec3 colour;
    GLfloat ambientIntensity;
};

# endif