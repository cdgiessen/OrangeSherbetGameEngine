#version 410 core
layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexturePos;

uniform MatrixBlob {
    mat4 model;
    mat4 view;
    mat4 proj;
	mat4 normal;
} matrices;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

out vec2 texturePos;
out vec3 fragmentPos;
out vec3 normalDir;

void main()
{
    gl_Position = proj * view * model * vec4(VertexPos, 1.0f); 
	fragmentPos = vec3(view * model * vec4(VertexPos, 1.0f)); // fragment position in camera space
	normalDir = normalMat * VertexNormal;
	texturePos = VertexTexturePos;
}
