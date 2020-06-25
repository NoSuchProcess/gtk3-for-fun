#version 330 core
in vec3 vert;
in vec3 vertNormal;
out vec4 fragColor;

uniform vec3 lightPos;

void main()
{
    vec3 L = normalize(lightPos - vert);
    float NL = max(dot(normalize(vertNormal), L), 0.0);
    vec3 color = vec3(0.39, 1.0, 0.0);
    vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);
    fragColor = vec4(col, 1.0);
}
