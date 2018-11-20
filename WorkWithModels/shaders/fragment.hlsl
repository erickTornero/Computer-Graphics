#version 330                        
                                    
in vec4 vCol;                       
in vec2 TexCoord;
in vec3 Normal;

out vec4 colour;                    

struct DirectionalLight{
    vec3 colour;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};
uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main(){                        
    //colour = vec4(1.0,0.0,0.0,1.0);
    //colour = vCol;
    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;               
    
    // ** Get the cos(Theta angle)
    // ** if The angle is less than 0 so return 0.0f.
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
    colour = texture(theTexture, TexCoord) * (ambientColour + diffuseColour);  
}