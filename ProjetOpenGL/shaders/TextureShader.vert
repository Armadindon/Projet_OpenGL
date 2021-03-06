#version 120

// attribute = input du VERTEX shader
attribute vec3 a_position;
attribute vec3 a_texcoords;
attribute vec3 a_normal;


// varying = output du VERTEX shader et INPUT du FRAGMENT shader
varying vec2 v_texcoords;
varying vec3 v_normal;
varying vec3 v_fragPos;

uniform mat4 u_projection;
uniform mat4 u_world;
uniform mat4 u_view;
uniform mat4 u_normalMatrix;
uniform mat4 u_mvp;

void main(void) 
{
	// stpq alias de xyzw alias de rgba
	v_texcoords = vec2(a_texcoords.s, 1.0 - a_texcoords.t);

	v_fragPos = vec3(u_world * vec4(a_position, 1.0));
	//On transcrit la position des normales sur l'objet vers les positions dans le monde
	v_normal = mat3(u_normalMatrix) * a_normal;

	gl_Position = u_mvp * vec4(a_position, 1.0);
	//u_projection * u_view * u_world * vec4(a_position, 1.0); //en changeant la pos, on ?loigne le PDV/"cam?ra"
}