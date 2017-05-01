# version 330

in vec2 InterpolatedTexCoord;
in vec3 InterpolatedColor;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;

void main()
{
	FragColor = texture2D(DiffuseTexture, InterpolatedTexCoord) * vec4(InterpolatedColor, 1.0);
}