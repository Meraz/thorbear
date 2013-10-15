#version 400

struct Particle {
  vec3 translation;
  vec3 scale;
  vec3 color;
};

in Particle gParticle;
in float gDiffuse;

out vec4 fColor;
 
void main(void)
{
  fColor = vec4( gParticle.color, 1 );
  
	fColor = vec4( gParticle.color * gDiffuse, 1 );
}
