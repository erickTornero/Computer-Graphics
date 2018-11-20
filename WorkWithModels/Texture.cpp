# include "Texture.hpp"


bool Texture::LoadTexture(){
    unsigned char * texData = stbi_load(this->fileLocation, &this->width, &this->height, &this->bitDepht, 0);
    if(!texData){
        printf("Failed Loading the file texture\n");
        return false;
    }
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D ,this->textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
    
    return true;
}

bool Texture::LoadTextureA(){
    unsigned char * texData = stbi_load(this->fileLocation, &this->width, &this->height, &this->bitDepht, 0);
    if(!texData){
        printf("Failed Loading the file texture\n");
        return false;
    }
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D ,this->textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);

    return true;
}


void Texture::UseTexture(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}
void Texture::ClearTexture(){
    glDeleteTextures(1, &textureID);
    this->textureID = 0;
    this->width = 0;
    this->height = 0;
    this->bitDepht = 0;
    this->fileLocation = "";
}

Texture::~Texture(){
    this->ClearTexture();
}