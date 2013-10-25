//=============================================================================
// transform.fx by Frank Luna (C) 2004 All Rights Reserved.
//
// Basic FX that simply transforms geometry from local space to 
// homogeneous clip space, and draws the geometry in wireframe mode.
//=============================================================================

uniform extern float4x4 gWVP;
uniform extern texture gTexture;


//sampler
sampler TexS = sampler_state
{
	Texture = <gTexture>;     //define which texture we're using in the sampler
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;       //Don't worry too much about these 3 for now.  They're defining how linear interpolation is calculated on the texture
	AddressU = WRAP;
	AddressV = WRAP;		  //These define how the sampler reacts when we pass it a UV value outside the 0-1 bound.  Wrap tells it to wrap around on whichever axis
};

//This shader will only transform verts	
struct OutputVS
{
    float4 posH : POSITION0;
	float2 tex0 : TEXCOORD0;
};

// Define the vertex shader program.  The parameter posL 
// corresponds to a data member in the vertex structure.
// Specifically, it corresponds to the data member in the 
// vertex structure with usage D3DDECLUSAGE_POSITION and 
// index 0 (as specified by the vertex declaration).
OutputVS TransformVS(float3 posL : POSITION0, float2 tex0 : TEXCOORD0)
{
    // Zero out our output.
	OutputVS outVS = (OutputVS)0;

	// Transform to homogeneous clip space.
	//float4x4 combo = mul(gScaleMat, gTranslateMat);
	//combo = mul(combo, gRotationMat);
	//combo = mul(combo, gWVP);

	//assign new position
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	outVS.tex0 = tex0;

	// Done--return the output.
    return outVS;
}

// Define the pixel shader program.  Just return a 4D color
// vector (i.e., first component red, second component green,
// third component blue, fourth component alpha).  Here we
// specify black to color the lines black. 
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

technique TransformTech
{
    pass P0
    {
		Lighting = TRUE;
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_3_0 TransformVS();
        pixelShader  = compile ps_3_0 TransformPS();

		// Specify the render/device states associated with this pass.
		//FillMode = Wireframe;
    }
}