#ifndef __SHADOWMAPM__
#define __SHADOWMAPM__
#include <GL/glew.h>
class ShadowMap{
public:
    ShadowMap();
    virtual bool Init(GLuint width, GLuint height);
    virtual void Write();
    virtual void Read(GLenum textureUnit);

    GLuint GetShadowWidth(){return shadowWidth;}
    GLuint GetShadowHeight(){return shadowHeight;}   

    ~ShadowMap();
private:
    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;

};

#endif