#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;
  
uniform sampler2D ourTexture;
uniform vec3 lightColor;

void main()
{
    // ambient
    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = vec4(lightColor, 1.0);
}