#version 330                        
                                    
in vec4 vCol;                       
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 colour;                    

struct DirectionalLight{
    vec3 colour;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

struct Material{
    float specularIntensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eyePosition;

void main(){                        
    //colour = vec4(1.0,0.0,0.0,1.0);
    //colour = vCol;
    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;               
    
    // ** Get the cos(Theta angle)
    // ** if The angle is less than 0 so return 0.0f.
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
    vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
    
    vec4 specularColour = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f){
        vec3 fragToEye = normalize(eyePosition - FragPos);
        // Reflect the directional Light over the normal
        vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(Normal)));

        float specularFactor = dot(fragToEye, reflectedVertex);

        if(specularFactor > 0.0f){
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(directionalLight.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }
    colour = texture(theTexture, TexCoord) * (ambientColour + diffuseColour + specularColour);  
}