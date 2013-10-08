cbuffer cbPerObject
{
	float4x4 gWVP; 
	float4x4 gWorld;
	float4 	gDirToSunW = float4(0,0,-1,1);
	float4  gColor;
};

Texture2D gTexture;

SamplerState gTriLinearSam
{
	Filter = ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
};

BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

struct VS_IN
{
	float3 posL    : POSITION;
	float3 normalL : NORMAL;
	float2 texC	   : TEXCOORD0;
	float4 diffuse : DIFFUSE;
	float4 spec    : SPECULAR;
};

struct VS_OUT
{
	float4 posH         : SV_POSITION;
	float3 posW			: POSITION;
	float4 normalW		: NORMAL;
	float2 stretchedUV  : TEXCOORD1;
	float4 diffuse		: DIFFUSE;
    float4 spec			: SPECULAR;
	float shade			: SHADE;
};

VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;

	vOut.posW = mul(float4(vIn.posL, 1.0f), gWorld).xyz;
	// Transform to homogeneous clip space.
	vOut.posH = mul(float4(vIn.posL, 1.0f), gWVP);

	vOut.normalW = mul(float4(vIn.normalL, 0.0f), gWorld);

	float4 temp = normalize(gDirToSunW);

	vOut.shade = saturate(max(dot(vOut.normalW, temp), 0.0f) + 0.3f);

	vOut.stretchedUV = vIn.texC;
	vOut.diffuse = vIn.diffuse;
	vOut.spec    = vIn.spec;

	return vOut;
}

float4 PS(VS_OUT pIn) : SV_Target
{
	float4 C = gTexture.Sample(gTriLinearSam, pIn.stretchedUV);

	/*C *= pIn.shade;
	C *= gColor;*/
	
	return C; 	
}

RasterizerState Wireframe
{
	FillMode = Solid;
	CullMode = None;    
};

technique10 Color
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
        //SetBlendState(NoBlend, float4(0.0f,0.0f,0.0f,0.0f), 0xFFFFFFFF);
        SetRasterizerState(Wireframe);
    }
}