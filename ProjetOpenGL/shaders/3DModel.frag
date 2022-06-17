#version 120

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
//TODO: Gestion materiaux et textures
varying vec2 v_texcoords;
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_fragPos;

uniform sampler2D u_sampler;
uniform vec4 u_color;
uniform vec3 u_cameraPos;

//ambiant lighting
uniform vec3 u_lightPos;
uniform vec4 u_ambiantColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;

//Material
uniform Material u_material;



void main(void) {
    // Lumière ambiante
    vec4 ambiant = u_ambiantColor * vec4(u_material.ambient, 1.0);

    // Lumière diffuse
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = u_diffuseColor * (diff * vec4(u_material.diffuse, 1.0));

    // Lumière speculaire
    vec3 viewDir = normalize(u_cameraPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec4 specular = u_specularColor * (spec * vec4(u_material.specular, 1.0));  

    gl_FragColor = (ambiant + diffuse + specular) * u_color;
}
