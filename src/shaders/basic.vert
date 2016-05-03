attribute vec4 position;

uniform mat4 pr_matrix;

void main(void)
{


   gl_Position = pr_matrix * position;

} 