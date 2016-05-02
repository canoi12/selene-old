//#ifndef WINDOW_H
//#define WINDOW_H
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace selene {
	namespace graphics {

#define MAX_KEYS 	1024
#define MAX_BUTTONS 32

		class Window {
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

		
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			static double mx, my;
		public:
			Window(const char *name, int width, int height);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			inline int getWidth() const {return m_Width; }
			inline int getHeight() const {return m_Height; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			static void getMousePosition(double& x, double& y);
		private:
			bool init();
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}

}

//#endif /* WINDOW_H */