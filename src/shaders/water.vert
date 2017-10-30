#version 330

in vec2 v_Pos;
in vec3 v_Color;
in vec2 v_TexCoord;

out vec3 in_Color;
out vec2 in_TexCoord;

uniform mat4 world;
uniform mat4 view;
uniform mat4 model;

uniform vec4 spriteFrame;
out vec4 sprFrame;

uniform vec2 waveData;

void main() {
     in_Color = v_Color;
     in_TexCoord = v_TexCoord;
     sprFrame = spriteFrame;

     vec4 newPos = vec4(v_Pos.x + waveData.y * sin(waveData.x+v_Pos.x+v_Pos.y), v_Pos.y + waveData.y * cos(waveData.x+v_Pos.x+v_Pos.y), 0.0, 1.0);
     gl_Position = world * view * model * newPos;
}