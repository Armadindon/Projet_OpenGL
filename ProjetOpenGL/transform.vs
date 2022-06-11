#version 120

// attribute = input du VERTEX shader

attribute vec3 a_position;
attribute vec2 a_texcoords;

// varying = output du VERTEX shader et INPUT du FRAGMENT shader
//TODO: Gérer les matériaux + Textures

uniform mat4 u_projection;
uniform mat4 u_position;

void main(void) 
{
	gl_Position = u_projection * u_position * vec4(a_position, 1.0); //en changeant la pos, on éloigne le PDV/"caméra"
}