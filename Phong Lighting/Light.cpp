# include "Light.hpp"

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation){
    glUniform3f(ambientColourLocation, this->colour.x, this->colour.y, this->colour.z);
    glUniform1f(ambientIntensityLocation, this->ambientIntensity);
}

Light::~Light(){
    
}