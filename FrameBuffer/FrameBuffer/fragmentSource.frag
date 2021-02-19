#version 330 core  

out vec4 fragColor; 

in vec2 texCoord;

uniform sampler2D texture11;
uniform sampler2D texture12;

void main() {  
	fragColor = mix(texture(texture11, texCoord), texture(texture12, texCoord), 0.2);
}  