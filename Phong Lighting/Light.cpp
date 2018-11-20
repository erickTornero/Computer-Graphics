# include "Light.hpp"

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation){
    glUniform3f(ambientColourLocation, this->colour.x, this->colour.y, this->colour.z);
    glUniform1f(ambientIntensityLocation, this->ambientIntensity);
    glUniform3f(directionLocation, this->direction.x, this->direction.y, this->direction.z);
    glUniform1f(diffuseIntensityLocation, this->diffuseIntensity);
}

Light::~Light(){

}