#version 330                        
                                    
in vec4 vCol;                       
                                    
out vec4 colour;                    
                                    
void main(){                        
    //colour = vec4(1.0,0.0,0.0,1.0);
    colour = vCol;                  
}