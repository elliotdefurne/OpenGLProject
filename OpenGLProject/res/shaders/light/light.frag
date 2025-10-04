#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor, 1.0); // applique la couleur de la lumiere sur la texture
}
