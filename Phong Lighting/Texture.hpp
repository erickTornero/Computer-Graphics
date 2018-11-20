# ifndef __TEXTUREM__
# define __TEXTUREM__

# include <GL/glew.h>

#include "stb_image.h"

class Texture{
public:
    Texture(char * fileLoc = ""):textureID(0),width(0), height(0), bitDepht(0), fileLocation(fileLoc){};

    void LoadTexture();
    void UseTexture();

    void ClearTexture();
    ~Texture();

private:
    GLuint textureID;
    int width, height, bitDepht;

    char * fileLocation;
};

# endif