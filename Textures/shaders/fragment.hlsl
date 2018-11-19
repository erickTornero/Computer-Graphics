#version 330                        
                                    
in vec4 vCol;                       
in vec2 TexCoord;

out vec4 colour;                    

uniform sampler2D theTexture;

void main(){                        
    //colour = vec4(1.0,0.0,0.0,1.0);
    //colour = vCol;               
    colour = texture(theTexture, TexCoord);   
}