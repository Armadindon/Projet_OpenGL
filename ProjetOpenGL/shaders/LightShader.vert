#version 120

// attribute = input du VERTEX shader
attribute vec3 a_position;


// varying = output du VERTEX shader et INPUT du FRAGMENT shader
//TODO: G�rer les mat�riaux + Textures

uniform mat4 u_projection;
uniform mat4 u_world;

void main(void) 
{
	gl_Position = u_projection * u_world * vec4(a_position, 1.0); //en changeant la pos, on �loigne le PDV/"cam�ra"
}