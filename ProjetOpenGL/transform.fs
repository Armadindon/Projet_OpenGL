#version 120


// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
//TODO: Gestion materiaux et textures
varying vec2 v_texcoords;
varying vec4 v_color;

uniform sampler2D u_sampler;

void main(void) {
    //Temporaire: On affiche le modèle en blanc
    gl_FragColor = vec4(1, 1, 1, 1);
}
