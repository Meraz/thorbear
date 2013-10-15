#version 400

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

in Particle vParticle;

out vec4 fColor;
 
void main(void)
{
  fColor = vParticle.color;
}
