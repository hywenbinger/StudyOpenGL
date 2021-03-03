#version 330 core  

layout(location = 0) in vec3 aPos;   

out vec3 texCoords;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

void main(){  
	texCoords = aPos;
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0); 
}