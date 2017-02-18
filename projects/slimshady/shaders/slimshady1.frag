#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform vec4 blendColor;
// Custom parameters from Sprite
uniform vec3 customParams[8];
uniform sampler1D palette;

void main()
{
	// gl_FragCoord = screen coords. bottom-left: 0.5,0.5 top-right: 1279.5,719.5
	vec2 mapped = vec2(gl_FragCoord.x / customParams[0].x, gl_FragCoord.y / customParams[0].y); // between 0.0f and 1.0f
	gl_FragColor = vec4(sin(customParams[1].x)*mapped.x, cos(customParams[1].y)*mapped.y, sin(customParams[1].y+3.1415926)*mapped.x, 1.0);
}
