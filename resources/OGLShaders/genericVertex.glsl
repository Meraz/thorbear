// set shader model version to 1.5 (opengl 3.3), use 420 for version 4.2
#version 400
#extension GL_ARB_explicit_attrib_location : enable


layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 vertexNormal; 


uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 lightPosition;

// Diffuse
uniform vec3 intensityDiffuse;

out vec3 normal;
out vec2 uv;

out vec4 eyeCoords;
out vec3 lightVec;

out vec3 diffuse;


void main()
{
	normal = normalize( normalMatrix * vertexNormal );
	uv = vertexUV;

	eyeCoords = modelViewMatrix * vec4( vertexPosition, 1.0f );

	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
	diffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;

	gl_Position = projectionMatrix * eyeCoords;
}
