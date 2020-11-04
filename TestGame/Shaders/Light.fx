
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
	float4 ambientColor;
	float4 diffuseColor;
	float specularPower;
	float4 specularColor;
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
	float3 viewDirection : TEXCOORD1;
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
	
	// Calculate the position of the vertex in the world.
	float4 worldPosition = mul(input.position, worldMatrix);
	
	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = (1.0f, 1.0f, 1.0f) - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

    
	return output;
}

float4 PSMain(PixelInputType input) : SV_TARGET
{
	float4 texColor;
	float4 normals;
	float3 lightDir;
	float lightIntensity;
	float4 outputColor;

    // Sample the colors from the color render texture using the point sampler at this texture coordinate location.
	texColor = colorTexture.Sample(SampleTypePoint, input.tex);
	
	outputColor = ambientColor;
	
	// Initialize the specular color.
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
    // Sample the normals from the normal render texture using the point sampler at this texture coordinate location.
	normals = normalTexture.Sample(SampleTypePoint, input.tex);

    // Invert the light direction for calculations.
	lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(normals.xyz, lightDir));
	//if (lightIntensity > 0.0f)
	//{
	//	// Determine the final diffuse                     color based on the diffuse color and the amount of light intensity.
	//	outputColor += (diffuseColor * lightIntensity);
	//	// Saturate the ambient and diffuse color.
	//	outputColor = saturate(outputColor);
	//	// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
	//	float3 reflection = normalize(2 * lightIntensity * normals.xyz - lightDir);
	//	// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
	//	specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	//}
	
	//// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	//outputColor = outputColor * texColor;

	//// Add the specular component last to the output color.
	//outputColor = saturate(outputColor + specular);
	
    // Determine the final amount of diffuse color based on the color of the pixel combined with the light intensity.
	outputColor = saturate(texColor * lightIntensity);

	return outputColor;
}

