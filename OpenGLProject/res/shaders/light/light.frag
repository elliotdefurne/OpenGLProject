#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;  

uniform sampler2D ourTexture;
uniform vec3 lightColor;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = texColor;
}