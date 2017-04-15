#version 400 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexturePosition;

uniform MVPUniform {
    mat4 model;
    mat4 view;
    mat4 proj;
} mvp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 texturePos;
out vec3 fragmentPos;
out vec3 normalDir;
out vec3 lightPos;

//void getEyeSpace( out vec3 norm, out vec4 position )
//{
//	norm = normalize( mat3(transpose(inverse(view * model))) * normal);
//	position = view * model * vec4(VertexPosition,1.0);
//}

void main()
{
    gl_Position = proj * view * model * vec4(VertexPosition, 1.0f); 
	fragmentPos = vec3(view * model * vec4(VertexPosition, 1.0f));
	normalDir = mat3(transpose(inverse(view * model))) * VertexNormal;
	texturePos = VertexTexturePosition;

	lightPos = vec3(view * vec4(0.5f, 1.5f, 0.0f, 1.0)); // Transform world-space light position to view-space light position
}
