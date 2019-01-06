# include "ShadowMap.hpp"

ShadowMap::ShadowMap(){
    this->FBO = 0;
    this->shadowMap = 0;
}
bool ShadowMap::Init(GLuint width, GLuint height){
    this->shadowWidth = width;
    this->shadowHeight = height;
    glGenFramebuffers(1, &FBO);  
}