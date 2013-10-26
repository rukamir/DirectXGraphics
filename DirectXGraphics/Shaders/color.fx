//=============================================================================
// color.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Basic FX that simply transforms geometry from local space to 
// homogeneous clip space, and draws the geometry in solid color.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern float4 CustCol;
uniform extern texture gTexture;

sampler TexS = sampler_state
{
	Texture = <gTexture>;     //define which texture we're using in the sampler
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;       //Don't worry too much about these 3 for now.  They're defining how linear interpolation is calculated on the texture
	AddressU = WRAP;
	AddressV = WRAP;		  //These define how the sampler reacts when we pass it a UV value outside the 0-1 bound.  Wrap tells it to wrap around on whichever axis
};

struct OutputVS
{
    float4 posH  : POSITION0;
    float4 color : COLOR0;
	float2 tex0 : TEXCOORD0;
};


OutputVS ColorVS(float3 posL : POSITION0, float4 c : COLOR0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	// Just pass the vertex color into the pixel shader.
	outVS.color = c;
	 
	// Done--return the output.
    return outVS;
}

float4 ColorPS(float4 c : COLOR0) : COLOR
{
	return CustCol;
    //return c;
	//return float4(0.0f, 1.0f, 0.0f, 1.0f);
}

float4 TransformPS(float2 tex0: TEXCOORD0) : COLOR
{
	//The tex0 that's passed in is linear interpolated, which means it's calculating the "estimated value" based on the distance between the vertexes in the containing triangle
	//and averaging their UV coords based on that weight... it's complicated, but it does it for you
	float3 texcolor = tex2D(TexS, tex0).rgb;

	//return that value (the 1.0 here is saying we're saying no alpha always, and not pulling that channel from the texture
	return float4(texcolor, 1.0f);


	//color component returns are typically 0.0 - 1.0f
    //return float4(0.0f, 1.0f, 0.0f, 1.0f);
	//            R     G     B     A (1.0f = completely opaque, no alpha)
}

technique ColorTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_3_0 ColorVS();
        pixelShader  = compile ps_3_0 TransformPS();//;ColorPS();

		//FillMode = Wireframe;
    }

	pass P1
	{
		//pixelShader  = compile ps_3_0 TransformPS();
	}
}