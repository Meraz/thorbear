#version 400

layout(points) in;
layout(triangle_strip, max_vertices=14) out;

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

uniform mat4 worldProjectionMatrix;
 
in Particle vParticle[];

out Particle gParticle;
 
void main(void)
{
  float x = vParticle[0].scale.x*2;
  float y = vParticle[0].scale.y*2;
  float z = vParticle[0].scale.z*2;
  vec4 trans = vec4( vParticle[0].translation, 0 );
  
  gParticle = vParticle[0];
  
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, -y, z, 1));
  EmitVertex(); // 0
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, z, 1));
  EmitVertex(); // 1
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, y, z, 1));
  EmitVertex(); // 2
  gl_Position = worldProjectionMatrix * (trans + vec4(x, y, z, 1));
  EmitVertex(); // 3
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, -z, 1));
  EmitVertex(); // 7
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, z, 1));
  EmitVertex(); // 1
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, -z, 1));
  EmitVertex(); // 5
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, -y, -z, 1));
  EmitVertex(); // 4
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, -z, 1));
  EmitVertex(); // 7
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, y, -z, 1));
  EmitVertex(); // 6
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, y, z, 1));
  EmitVertex(); // 2
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, -y, -z, 1));
  EmitVertex(); // 4
  gl_Position = worldProjectionMatrix * (trans + vec4(-x, -y, z, 1));
  EmitVertex(); // 0
  gl_Position = worldProjectionMatrix * (trans + vec4(x, -y, z, 1));
  EmitVertex(); // 1
}
