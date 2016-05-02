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

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Shader shader("src/shaders/basic.vert","src/shaders/basic.frag");

	while(!window.closed())
	{
		glVertex2f(-0.5f,-0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f,-0.5f);
		window.clear();
		glDrawArrays(GL_ARRAY_BUFFER,0,6);
		window.update();
	}
	return 0;
}