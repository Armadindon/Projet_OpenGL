#version 120

// attribute = input du VERTEX shader
attribute vec3 a_position;

uniform mat4 u_projection;
uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_mvp;

void main(void) 
{
	gl_Position = u_mvp * vec4(a_position, 1.0); //en changeant la pos, on éloigne le PDV/"caméra"
}