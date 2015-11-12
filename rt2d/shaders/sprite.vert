#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition; // in modelspace
attribute vec2 vertexUV;

// Output data; will be interpolated for each fragment.
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec2 UVoffset;

void main()
{
	// Output position of the vertex, in clip space: MVP * position
	gl_Position = MVP * vec4(vertexPosition, 1);

	// UV of the vertex
	UV = vertexUV + UVoffset;
}
