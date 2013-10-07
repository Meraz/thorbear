cbuffer cbPerObject
{
	float4x4 gVP;
	float4 	gDirToSunW = float4(0,0,-1,1);
};

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
	row_major float4x4 mTransform : mTransform;
};

struct VS_OUT
{
	float4 posH         : SV_POSITION;
	float shade			: SHADE;
};

VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;

	float4x4 WVP = mul(vIn.mTransform, gVP);
	vOut.posH = mul(float4(vIn.posL, 1.0f), WVP);

	float4 normalW = mul(float4(vIn.normalL, 0.0f), vIn.mTransform);

	float4 temp = normalize(gDirToSunW);

	vOut.shade = saturate(max(dot(normalW, temp), 0.0f) + 0.3f);

	return vOut;
}

float4 PS(VS_OUT pIn) : SV_Target
{

	float4 C = float4(0.0f, 1.0f, 0.0f, 1.0f) * pIn.shade;
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

