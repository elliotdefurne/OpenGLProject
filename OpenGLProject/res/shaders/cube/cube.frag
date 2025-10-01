#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    FragColor = vec4((ambient+diffuse) * texColor.rgb, texColor.a);
}