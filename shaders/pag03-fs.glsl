#version 410

out vec4 colorFragmento;
in vec3 vertexColor;

void main ()
{
    colorFragmento = vec4 ( vertexColor, 1.0 );
}