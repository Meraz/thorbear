#version 400

layout(points) in;
layout(triangle_strip, max_vertices=14) out;

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

uniform mat4 worldProjectionMatrix;
 
in Particle vParticle;

out Particle gParticle;
 
void main(void)
{
  float x = vParticle.scale.x;
  float y = vParticle.scale.y;
  float z = vParticle.scale.z;
  
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, -y, z, 1));
  EmitVertex(); // 0
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, z, 1));
  EmitVertex(); // 1
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, y, z, 1));
  EmitVertex(); // 2
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, y, z, 1));
  EmitVertex(); // 3
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, -z, 1));
  EmitVertex(); // 7
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, z, 1));
  EmitVertex(); // 1
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, -z, 1));
  EmitVertex(); // 5
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, -y, -z, 1));
  EmitVertex(); // 4
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, -z, 1));
  EmitVertex(); // 7
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, y, -z, 1));
  EmitVertex(); // 6
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, y, z, 1));
  EmitVertex(); // 2
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, -y, -z, 1));
  EmitVertex(); // 4
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(-x, -y, z, 1));
  EmitVertex(); // 0
  gl_Position = worldProjectionMatrix * (vec4( particleData.translation, 0 ) + vec4(x, -y, z, 1));
  EmitVertex(); // 1
  
  gParticle = vParticle;
}
