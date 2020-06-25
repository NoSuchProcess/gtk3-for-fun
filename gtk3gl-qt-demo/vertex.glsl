#version 330 core
in vec3 position;
in vec3 normal;
out vec3 vert;
out vec3 vertNormal;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main()
{
    vert = position;
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * mvMatrix * vec4(position, 1.0);
}
