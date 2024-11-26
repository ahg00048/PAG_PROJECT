#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 diffColor;

out salidaVS {
    vec3 vertexPos;
    vec3 vertexNormal;
    vec3 vertexColor;
} salida;

void main () {
    salida.vertexColor = diffColor;
    salida.vertexPos = vec3 ( view * model * vec4 ( posicion, 1.0f ) );
    salida.vertexNormal = vec3 ( view * model * vec4( normal, 0.0f ) );
    gl_Position = projection * view * model * vec4 ( posicion, 1.0f );
}