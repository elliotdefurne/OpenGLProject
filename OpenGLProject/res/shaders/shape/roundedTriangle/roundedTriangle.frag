// --- Fragment Shader ---
#version 330 core
out vec4 FragColor;

uniform vec3 color;

uniform vec2 uResolution;

// SDF for equilateral triangle centered at origin
float sdTriangle(vec2 p, float r) {
    const float k = sqrt(3.0);
    p.x = abs(p.x) - r;
    p.y = p.y + r / k;
    if (p.x + k * p.y > 0.0)
        p = vec2(p.x - k * p.y, -k * p.x - p.y) / 2.0;
    p.x -= clamp(p.x, -2.0 * r, 0.0);
    return -length(p) * sign(p.y);
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * uResolution) / uResolution.y;

    float size   = 0.35;   // triangle size
    float radius = 0.28;   // corner rounding radius

    // SDF value (negative = inside)
    float d = sdTriangle(uv, size) + radius;

    // Anti-aliased edge
    float shape = smoothstep(0.005, -0.005, d);

    vec3 color = mix(vec3(0.1), vec3(0.2, 0.6, 1.0), shape);
    FragColor = vec4(color, 1.0);
}