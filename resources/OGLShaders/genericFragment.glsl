#version 150

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
uniform vec3 Ka;
uniform vec3 Ia;

// Diffuse
uniform vec3 Kd;

// Specular
uniform vec3 Ks;
uniform float c3;
uniform vec3 Is;

uniform sampler2D map_Kd;

in vec3 vShadowCoord;
uniform sampler2DShadow shadowmap;


out vec3 fragmentColour;


void main()
{
	vec4 mKd;
	vec3 specular;

	float shadow = 0.0;
	vec4 sc = vec4(vShadowCoord, 1.f);
	sc.z -= 0.001;
	shadow += textureProjOffset (shadowmap, sc, ivec2 (-1, 1));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (1, 1));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (-1, -1));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (1, -1));
	shadow *= 0.5;
	shadow += textureProjOffset (shadowmap, sc, ivec2 (-1, 0));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (1, 0));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (0, -1));
	shadow += textureProjOffset (shadowmap, sc, ivec2 (0, 1));
	shadow *= 0.5;
	shadow += textureProjOffset (shadowmap, sc, ivec2 (0, 0));
	shadow *= 0.25;
	
	if ( shadow > 0 )
	{
		mKd = texture(map_Kd, uv);

		vec3 Ir = vec3( 0.0f ); // reflection from reflection map

		vec3 n = normalize( normal );
		//vec3 s = normalize( vec3( lightPos - eyeCoords ) );
		vec3 v = normalize( -vec3( eyeCoords ) );
		vec3 r = reflect( -normalize( lightVec ), normal );
	
		// ToDo: Kd -> map_Kd
		specular = pow ( max( 0.0f, dot( r, v ) ), c3 ) * Is + Ir;
	}

	fragmentColour = vec3(Ka * Ia + shadow * ( vec3( mKd ) * diffuse + Ks * specular ) );

	//fragmentColour = mKd;
	//fragmentColour = vec4(Ka * Ia, 1.0f);
	//fragmentColour = vec4(abs(normal), 1.0);
}
