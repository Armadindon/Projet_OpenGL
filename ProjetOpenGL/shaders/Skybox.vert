#version 330 core

// attribute = input du VERTEX shader
attribute vec3 a_position;

// varying = output du VERTEX shader et INPUT du FRAGMENT shader
//TODO: Gérer les matériaux + Textures
varying vec3 v_texCoords;

uniform mat4 u_projection;
uniform mat4 u_view;

void main(void) 
{
    v_texCoords = a_position;
    //En faisant mat4(mat3(u_view)), on ignore la translation de la caméra
    gl_Position = u_projection * mat4(mat3(u_view)) * vec4(a_position, 1.0); //en changeant la pos, on éloigne le PDV/"caméra"
}