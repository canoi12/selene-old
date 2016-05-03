uniform vec4 colour;
uniform vec2 light_pos;

varying vec4 pos;

void main (void)  
{     
   float intensity = 1.0 / length(pos.xy - light_pos);
   gl_FragColor = colour * intensity;  
} 