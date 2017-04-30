#version 330

in vec3 VertexPosition;
in vec2 VertexTexCoord;
in vec3 VertexColor;

out vec3 InterpolatedColor;
out vec2 InterpolatedTexCoord;

uniform mat4 mvpMatrix;

void main()
{
	InterpolatedTexCoord = VertexTexCoord;
	InterpolatedColor = VertexColor;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
}