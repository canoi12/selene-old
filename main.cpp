#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

int main()
{
	using namespace selene;
	using namespace graphics;
	using namespace maths;

	Window window("Selene Engine",640,480);
	glClearColor(0.2f,0.3f,0.8f,1.0f);


	/*GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);*/
	
	/*glVertex2f(-0.5f,-0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f,-0.5f);*/
	
	GLfloat vertices[] = {
		4,3,0,
		12,3,0,
		4,6,0
		
	};
	
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	mat4 ortho = mat4::orthographic(0.0f,16.0f,0.0f,9.0f,-1.0f,1.0f);
	

	Shader shader("src/shaders/basic.vert","src/shaders/basic.frag");
	shader.enable();

	glUniformMatrix4fv(glGetUniformLocation(shader.m_ShaderID, "pr_matrix"), 1, GL_FALSE, ortho.elements);

	while(!window.closed())
	{
		if(window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			return 0;
		}
		window.clear();
		glDrawArrays(GL_TRIANGLES,0,6);
		window.update();
	}
	return 0;
}