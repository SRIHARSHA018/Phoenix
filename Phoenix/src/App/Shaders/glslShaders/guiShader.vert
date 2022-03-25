#version 460 core

layout(location = 0) in vec2 aPosition;

uniform mat4 u_uimodel;
uniform mat4 u_uiproj;
void main(){
	gl_Position = u_uiproj * u_uimodel*vec4(aPosition,0.0,1.0f);
}