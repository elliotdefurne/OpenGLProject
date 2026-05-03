#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 color; // the color you want

void main()
{
    vec4 tex = texture(texture1, TexCoords);

    // Use alpha as mask, replace color
    FragColor = vec4(color, tex.a);
}