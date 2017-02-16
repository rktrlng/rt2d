#version 120

// Custom parameters from Sprite
uniform vec3 customParams[8];

// Interpolated values from the vertex shaders
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;
uniform vec4 blendColor;

void main() {
	vec3 resolution = vec3(customParams[0].x, customParams[0].y, 0.0);

	vec3 mapped = vec3(gl_FragCoord.x / customParams[0].x, gl_FragCoord.y / customParams[0].y, 0.0); // between 0.0f and 1.0f

	float sum = 0;
	int i;
	for (i=2; i<8; i++) {
		sum += 10 / distance(customParams[i], mapped);
	}
	sum /= 200;

	if (sum > 0.99)
    	gl_FragColor = vec4( sum, sum, sum, 1.0 );
}
