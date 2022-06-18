#version 120

// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
varying vec2 v_texcoords;
varying vec3 v_normal;
varying vec3 v_fragPos;

uniform sampler2D u_sampler;

//ambiant lighting
uniform vec3 u_lightPos;
uniform vec4 u_ambiantColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;
uniform vec3 u_cameraPos;

void main(void) {
    // Lumière ambiante
    vec4 ambiant = u_ambiantColor;

    // Lumière diffuse
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = u_diffuseColor * diff;

    // Lumière speculaire
    vec3 viewDir = normalize(u_cameraPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec4 specular = u_specularColor * spec;  

    gl_FragColor = (ambiant + diffuse + specular) * texture2D(u_sampler, v_texcoords);;
}