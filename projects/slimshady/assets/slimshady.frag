#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform vec4 blendColor;

void main()
{
	// Output color = color of the texture at the specified UV
	//gl_FragColor = texture2D( textureSampler, UV ) * blendColor;

	vec4 customcolor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
	gl_FragColor = texture2D( textureSampler, UV ) * customcolor;
}
