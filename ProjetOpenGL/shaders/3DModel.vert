#version 120

// attribute = input du VERTEX shader

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoords;

// varying = output du VERTEX shader et INPUT du FRAGMENT shader
//TODO: Gérer les matériaux + Textures
varying vec3 v_normal;
varying vec3 v_fragPos;

uniform mat4 u_projection;
uniform mat4 u_world;
uniform mat4 u_view;

uniform mat4 u_normalMatrix;


void main(void) 
{
	//On transforme la position dans le monde à la position dans l'écran
	gl_Position = u_projection * u_view * u_world * vec4(a_position, 1.0); //en changeant la pos, on éloigne le PDV/"caméra"
	v_fragPos = vec3(u_world * vec4(a_position, 1.0));
	//On transcrit la position des normales sur l'objet vers les positions dans le monde
	v_normal = mat3(u_normalMatrix) * a_normal;
}