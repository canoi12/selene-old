#version 330

in vec3 in_Color;
in vec2 in_TexCoord;
in vec4 sprFrame;

out vec4 Color;

uniform sampler2D tex;

void main() {
     vec2 UV = sprFrame.xy + (in_TexCoord * sprFrame.zw);
     Color = texture(tex, UV) * vec4(in_Color, 1.0);
}