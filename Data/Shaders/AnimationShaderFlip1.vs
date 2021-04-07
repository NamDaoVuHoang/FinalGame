attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;
uniform 	mat4 	u_matWorld;
uniform 	float u_alpha;
uniform   float numFrames;
uniform   float currentFrames;
uniform   float currentRows;
uniform   float numRows;
varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	v_uv = vec2(1.0*(1.0-a_uv.x)/numFrames + 1.0/numFrames*currentFrames,1.0*(1.0-a_uv.y)/numRows + 1.0/numRows*currentRows);
}
   