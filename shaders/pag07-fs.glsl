#version 410

out vec4 colorFragmento;

in vec3 vertexColor;

in salidaVS {
    vec3 posicionV;
    vec3 normalV;
} entrada;

void main ()
{
    vec3 n = normalize ( entrada.normalV );
    colorFragmento = vec4 ( vertexColor, 1.0 );
}