#version 330

in vec3 in_Color;
//in vec2 in_TexCoord;

out vec4 Color;

void main() {
     Color = vec4(in_Color);
}