#version 330 core  

out vec4 fragColor; 

in vec2 texCoord;

uniform sampler2D texture21;

void main() {  
	fragColor = texture(texture21, texCoord);

//	fragColor = vec4(vec3(1.0 - texture(texture21, texCoord)), 1.0); //反相效果

//	fragColor = texture(texture21, texCoord);
//	float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
//    fragColor = vec4(average, average, average, 1.0); //灰度效果
}  