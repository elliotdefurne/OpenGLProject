#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform Material material;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    vec3 ambient = material.ambient * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  

    vec3 result = (ambient + diffuse + specular) * texColor.rgb;
    FragColor = vec4(result, 1.0);
}