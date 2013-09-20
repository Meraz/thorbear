#version 400

// In-data from VShader
in vec3 normal;
in vec2 uv;
in vec4 eyeCoords;
in vec3 lightVec;
in vec3 diffuse;

// Uniform data
// light and view/eye
uniform vec4 lightPos;

// Ambient
uniform vec3 coefficientAmbient;
uniform vec3 intensityAmbient;
uniform sampler2D mapAmbient;
// Diffuse
uniform vec3 coefficientDiffuse;
// uniform vec3 intensityDiffuse; // Taken care of in the Vertex already
uniform sampler2D mapDiffuse;
// Specular
uniform vec3 coefficientSpecular;
uniform float powerSpecular;
uniform vec3 intensitySpecular;
uniform sampler2D mapSpecular;

out vec3 fragmentColour;

void main()
{
	vec3 specularComponent;
	
  coefficientDiffuse = coefficientDiffuse + vec3(texture(mapDiffuse, uv));
  coefficientDiffuse = coefficientDiffuse + vec3(texture(mapAmbient, uv));
  coefficientSpecular = coefficientSpecular + vec3(texture(mapSpecular, uv));

  vec3 intensityReflection = vec3( 0.0f ); // reflection from reflection map

  vec3 n = normalize( normal );
  //vec3 s = normalize( vec3( lightPos - eyeCoords ) );
  vec3 v = normalize( -vec3( eyeCoords ) );
  vec3 r = reflect( -normalize( lightVec ), normal );

  specularComponent = pow ( max( 0.0f, dot( r, v ) ), powerSpecular ) * intensitySpecular + intensityReflection;

	fragmentColour = vec3(0.0f, 1.0f, 0.0f);
    //vec3(coefficientAmbient * intensityAmbient
    //+ ( coefficientDiffuse * diffuse + coefficientSpecular * specularComponent ) );

	//fragmentColour = mKd;
	//fragmentColour = vec4(Ka * Ia, 1.0f);
	//fragmentColour = vec4(abs(normal), 1.0);
}
