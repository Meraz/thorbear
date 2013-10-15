#version 400

layout(points) in;
layout(triangle_strip, max_vertices=14) out;

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 lightPos = vec4(0,0,0,1);
 
in Particle vParticle[];

out Particle gParticle;
out vec3 gDiffuse;
 
void main(void)
{
  float x = vParticle[0].scale.x*2;
  float y = vParticle[0].scale.y*2;
  float z = vParticle[0].scale.z*2;
  vec4 trans = vec4( vParticle[0].translation, 0 );
  
  gParticle = vParticle[0];
  
  vec3 eyeCoords;
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 0
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 1
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 2
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 3
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 7
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 1
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 5
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 4
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 7
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 6
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 2
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 4
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 0
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), normal ) ) * intensityDiffuse;
  gl_Position = worldProjectionMatrix * eyeCoords;
  EmitVertex(); // 1
}
