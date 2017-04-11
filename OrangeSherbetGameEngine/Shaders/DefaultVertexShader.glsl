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

out vec3 LightIntensity;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f); 
	fragmentPos = vec3(model * vec4(position, 1.0f));
	normalDir = mat3(transpose(inverse(model))) * normal;
	texturePos = textureCoord;

	vec3 tnorm = normalize( normalDir * normal);

	vec4 eyeCoords = model * vec4(position, 1.0);

	vec3 s = normalize(vec3(vec3(0,5,0) - eyeCoords));

	// The diffuse shading equation
	LightIntensity = vec3(1,1,1) * vec3(1,1,1) * max( dot( s, tnorm ), 0.0 );
}
