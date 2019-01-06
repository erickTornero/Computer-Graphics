# include "Material.hpp"

Material::Material(){
    this->specularIntensity = 0.0f;
    this->shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine){
    this->specularIntensity = sIntensity; 
    this->shininess = shine;
}

void Material::UseMaterial(GLuint specularItensityLocation, GLuint shininessLocation){
    glUniform1f(specularItensityLocation, this->specularIntensity);
    glUniform1f(shininessLocation, this->shininess);
}

Material::~Material(){
    
}