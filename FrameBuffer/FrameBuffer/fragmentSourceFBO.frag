#version 330 core  

out vec4 fragColor; 

in vec2 texCoord;

uniform sampler2D fboTexture;

void main() {  
	fragColor = texture(fboTexture, texCoord);
}  