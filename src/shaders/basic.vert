attribute vec4 position;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;

varying vec4 pos;

void main(void)
{
   gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
   pos = position;
} 