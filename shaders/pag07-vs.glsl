#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vertexColor;

out salidaVS {
    vec3 posicionV;
    vec3 normalV;
} salida;

void main ()
{
    gl_Position = projection * view * model * vec4 ( posicion, 1 );
    salida.posicionV = vec3 ( projection * view * model * vec4 ( posicion, 1) );

    vertexColor = color;
}