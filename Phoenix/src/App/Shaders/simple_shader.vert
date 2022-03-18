#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
  
//out vec3 ourColor;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

//uniform mat4 transforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;



void main()
{
    Normal = ((transpose(inverse(model)))* vec4(aNormal,0.f)).xyz;
    FragPos = vec3(model*vec4(aPos,1.0f));
    TexCoord = vec2(aTexCoord.x,aTexCoord.y);
    gl_Position = proj*view*vec4(FragPos, 1.0);
}     