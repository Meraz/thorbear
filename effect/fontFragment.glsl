#version 400
 
uniform sampler2D tex;
uniform vec4 color;

in vec2 texcoord;
 
void main(void) {
  gl_FragColor = vec4(vec3(1), texture2D(tex, texcoord).a) * color;
}