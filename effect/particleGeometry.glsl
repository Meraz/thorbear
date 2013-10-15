#version 400

layout(points) in;
layout(triangle_strip, max_vertices=24) out;

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 lightPosition = vec4(0,0,0,1);
 
in Particle vParticle[];

out Particle gParticle;
out float gDiffuse;
 
void main(void)
{
  float x = vParticle[0].scale.x*2;
  float y = vParticle[0].scale.y*2;
  float z = vParticle[0].scale.z*2;
  vec4 trans = vec4( vParticle[0].translation, 0 );
  
  gParticle = vParticle[0];
  
  vec4 eyeCoords;
  vec3 lightVec;
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, 1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 0
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, 1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 1
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, 1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 2
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, 1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 3
  EndPrimitive();
  
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 1
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 5
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 3
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 7
  EndPrimitive();
  
  
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, -1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 5
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, -1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 4
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, -1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 7
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 0, -1) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 6
  EndPrimitive();
  
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(-1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 4
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(-1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 0
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(-1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 6
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(-1, 0, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 2
  EndPrimitive();
  
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 7
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 6
  
  eyeCoords = viewMatrix * (trans + vec4(x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 3
  
  eyeCoords = viewMatrix * (trans + vec4(-x, y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, 1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 2
  
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, -1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 1
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, -1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 0
  
  eyeCoords = viewMatrix * (trans + vec4(x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, -1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 5
  
  eyeCoords = viewMatrix * (trans + vec4(-x, -y, -z, 1));
	lightVec = vec3( viewMatrix * lightPosition - eyeCoords );
  gDiffuse = max( 0.0f, dot( normalize( lightVec ), vec3(0, -1, 0) ) );
  gl_Position = projectionMatrix * eyeCoords;
  EmitVertex(); // 4
}
