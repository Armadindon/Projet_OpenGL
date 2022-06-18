#version 120
varying vec3 v_texCoords;

// texture de la skybox
uniform samplerCube u_skybox;

void main()
{    
    gl_FragColor = textureCube(u_skybox, v_texCoords);
}