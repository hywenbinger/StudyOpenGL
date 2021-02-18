#version 330 core  

layout(location = 6) in vec3 aPos;   
layout(location = 7) in vec2 aTexCoord;

out vec2 texCoord;

void main(){  
	gl_Position = vec4(aPos, 1.0); 
	texCoord = aTexCoord;
}