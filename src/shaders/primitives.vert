#version 330

in vec2 v_Pos;
//in vec2 v_Color;
//in vec2 v_TexCoord;

out vec4 in_Color;
//out vec2 in_TexCoord;

uniform vec4 v_Color;
uniform mat4 world;
uniform mat4 view;
uniform mat4 model;

void main() {
     gl_Position = world * view * model * vec4(v_Pos, 0.0, 1.0);

     in_Color = v_Color;
}