#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D myTexture;

void main() {
	
	vec3 result = vec3(texture(myTexture, texCoord));
	color = vec4(result, 1.0f);
}
