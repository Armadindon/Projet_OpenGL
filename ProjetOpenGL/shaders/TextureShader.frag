#version 120

// SORTIE DU VERTEX SHADER et INPUT du FRAGMENT SHADER
varying vec2 v_texcoords;

uniform sampler2D u_sampler;

void main(void) {
    gl_FragColor = texture2D(u_sampler, v_texcoords);;
}