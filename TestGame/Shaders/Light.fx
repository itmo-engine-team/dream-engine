
Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleTypePoint : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightBuffer : register(b1)
{
	float3 lightDirection;
	float padding;
};


struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


PixelInputType VSMain(VertexInputType input)
{
	PixelInputType output;
    
    
    // Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
    
    // Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
    
	return output;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;
	float3 lightDir;
	float lightIntensity;
	float4 outputColor;
	
    // Sample the colors from the color render texture using the point sampler at this texture coordinate location.
    colors = colorTexture.Sample(SampleTypePoint, input.tex);

    // Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
	normals = normalTexture.Sample(SampleTypePoint, input.tex);

    // Invert the light direction for calculations.
	lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(normals.xyz, lightDir));

    // Determine the final amount of diffuse color based on the color of the pixel combined with the light intensity.
	outputColor = saturate(colors * lightIntensity);

	return outputColor;
}

