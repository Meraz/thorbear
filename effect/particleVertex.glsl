#version 400

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};
 
layout(location = 0) in vec3 translation;
layout(location = 1) in vec3 scale;
layout(location = 2) in vec3 color;

out Particle vParticle;
 
void main(void)
{
  vParticle.translation = translation;
  vParticle.scale = scale;
  vParticle.color = color;
}
