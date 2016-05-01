#include "src/graphics/window.h"
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

	vec3 vector(1.0f,2.0f,3.0f);
	vector += vec3(5,2,10);

	while(!window.closed())
	{
		window.clear();
		std::cout << vector << std::endl;
#if 1
		glBegin(GL_QUADS);
		glVertex2f(-0.5f,-0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f,-0.5f);
		glEnd();
#endif
		glDrawArrays(GL_ARRAY_BUFFER,0,6);
		window.update();
	}
	return 0;
}