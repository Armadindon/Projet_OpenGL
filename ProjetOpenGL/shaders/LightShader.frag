#version 120


// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
uniform vec4 u_color;

void main(void) {
    //Temporaire: On affiche le mod�le en blanc
    gl_FragColor = u_color;
}
