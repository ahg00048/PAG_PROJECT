#version 410

out vec4 fragmentColor;

uniform vec3 Ka;
uniform vec3 Ks;
uniform vec3 Kd;
uniform float shininess;

uniform vec3 Ia;
uniform vec3 Is;
uniform vec3 Id;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform float gamma;
uniform float attenuation;

in salidaVS {
    vec3 vertexPos;
    vec3 vertexNormal;
    vec3 vertexColor;
    vec2 vertexTextCoord;
} entrada;

subroutine vec4 chooseColor();
subroutine uniform chooseColor uniformEleccionColor;

subroutine (chooseColor) vec4 colorTextura () {
    return vec4()
}

subroutine (chooseColor) vec4 colorMaterial () {
    return vec4();
}

subroutine vec3 calculateVertexColor();
subroutine uniform calculateVertexColor selected;

subroutine (calculateVertexColor) vec3 spotlight() {
    vec3 l = normalize ( lightPos - entrada.vertexPos );
    vec3 d = normalize ( lightDir );
    float cosGamma = cos ( gamma );
    float dotLD = dot( -l, d );
    float spotFactor = pow ( dotLD, attenuation );

    if ( dotLD < cosGamma ) { spotFactor = 0.0f; }

    vec3 n = normalize ( entrada.vertexNormal );
    vec3 v = normalize ( -entrada.vertexPos );
    vec3 r = reflect ( -l, n );

    vec3 diffuse = ( Id * Kd * max( dot( l, n ), 0.0f ) );
    vec3 specular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), shininess ) );

    return spotFactor * ( diffuse + specular );
}

subroutine (calculateVertexColor) vec3 point() {
    vec3 n = normalize ( entrada.vertexNormal );

    vec3 l = normalize ( lightPos - entrada.vertexPos );
    vec3 v = normalize ( -entrada.vertexPos );
    vec3 r = reflect ( -l, n );

    vec3 diffuse = ( Id * Kd * max( dot( l, n ), 0.0f ) );
    vec3 specular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), shininess ) );

    return diffuse + specular;
}

subroutine (calculateVertexColor) vec3 directional() {
    vec3 n = normalize ( entrada.vertexNormal );

    vec3 l = normalize ( -lightDir );
    vec3 v = normalize ( -entrada.vertexPos );
    vec3 r = reflect ( -l, n );

    vec3 diffuse = ( Id * Kd * max( dot( l, n ), 0.0f ) );
    vec3 specular = ( Is * Ks * pow ( max( dot( r, v ), 0.0f ), shininess ) );

    return diffuse + specular;
}

subroutine (calculateVertexColor) vec3 ambient() {
    vec3 ambient = ( Ia * Ka );
    return ambient;
}

void main() {
fragmentColor = vec4( selected(), 1.0f);
}