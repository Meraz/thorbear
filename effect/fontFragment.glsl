#version 400
 
uniform sampler2D tex;
uniform vec4 color;

in vec2 texcoord;

out vec4 fColor;
 
void main(void) {
  fColor = vec4(vec3(1), texture2D(tex, texcoord).a) * color;
}