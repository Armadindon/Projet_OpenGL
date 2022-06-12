#version 120


// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
//TODO: Gestion materiaux et textures
varying vec2 v_texcoords;
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_fragPos;

uniform sampler2D u_sampler;
uniform vec4 u_color;
//TODO: Mettre en place la matrice vue / caméra et supprimer la première ligne
vec3 u_view = vec3(0, 0, 0);
//uniform vec3 u_view;

//ambiant lighting
uniform vec4 u_ambiantLightColor;
uniform float u_ambiantLightStrength;

//difuse lighting
uniform vec3 u_lightPos;

//specular lighting
uniform float u_specularLightStrength;


void main(void) {
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //Todo: Définir la couleur de la diffuse light
    vec4 diffuse = diff * u_ambiantLightColor;

    vec4 ambiant = u_ambiantLightColor * u_ambiantLightStrength;

    vec3 viewDir = normalize(u_view - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = u_specularLightStrength * spec * u_ambiantLightColor;  

    gl_FragColor = (ambiant + diffuse + specular) * u_color;
}
