#version 410

out vec4 fragmentColor;

in salidaVS {
    vec3 vertexPos;
    vec3 vertexNormal;
    vec3 vertexColor;
} entrada;

subroutine vec3 calculateVertexColor();

subroutine (calculateVertexColor) vec3 colorRed() {
    return vec3 (1, 0, 0);
}

subroutine (calculateVertexColor) vec3 colorDiff() {
    return entrada.vertexColor;
}

subroutine uniform calculateVertexColor selected;

void main() {
    fragmentColor = vec4( selected(), 1.0f);
}