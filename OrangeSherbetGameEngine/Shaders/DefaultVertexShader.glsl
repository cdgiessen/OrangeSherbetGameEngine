#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texturePos;
out vec3 fragmentPos;
out vec3 normalDir;


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); 
	fragmentPos = vec3(model * vec4(position, 1.0f));
	normalDir = mat3(transpose(inverse(model))) * normal;
	texturePos = textureCoord;
}
