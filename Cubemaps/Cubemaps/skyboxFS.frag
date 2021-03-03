#version 330 core  

out vec3 texCoords;

out vec4 fragColor; 

uniform samplerCube skybox;

void main() {  
	fragColor = texture(skybox, texCoords);
}  