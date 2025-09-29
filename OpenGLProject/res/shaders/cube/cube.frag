#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 lightColor;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    FragColor = vec4(ambient * texColor.rgb, texColor.a);
}