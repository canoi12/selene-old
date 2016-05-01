#include <GLFW/glfw3.h>
#include <iostream>
#include "src/graphics/window.h"

int main()
{
	using namespace selene;
	using namespace graphics;

	Window window("Selene Engine",640,480);
	glClearColor(0.2f,0.3f,0.8f,1.0f);

	while(!window.closed())
	{
		window.clear();
		glBegin(GL_QUADS);
		glVertex2f(-0.5f,-0.5f);
		glVertex2f(-0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f,-0.5f);
		glEnd();
		window.update();
	}
	return 0;
}