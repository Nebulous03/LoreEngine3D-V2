#include "Window.h"
#include <iostream>

bool Window::glInitialized = false;

Window::Window(char* title, const int width, const int height, const int displayMode, const bool vsync, const bool resizable)
	: title(title), width(width), height(height), displayMode(displayMode), vsync(vsync), resizable(resizable) { }

Window::~Window()
{
	dispose();
}

void glErrorCallback(int error, const char* description)
{
	std::cout << "Fatal Error! : OpenGL encountered an internal error! [" << error << "]\n\t" << description << std::endl;
}

Window& Window::create()
{
	if (!glInitialized)
	{
		glfwSetErrorCallback(glErrorCallback);

		if (glfwInit() == GLFW_FALSE)
			std::cout << "Fatal Error! : OpenGL failed to initialize! (glfwInit() = GLFW_FALSE)" << std::endl;
		else
			std::cout << "GLFW initialized successfully!" << std::endl;

	}

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	build();

	if (!glInitialized) {

		if (glewInit() != GLEW_OK)
			std::cout << "Error! : Failed to initialize GLEW! (glewInit() == FALSE)" << std::endl;
		else
			std::cout << "GLEW initialized successfully!" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowSizeCallback(glWindow, window_size_callback);

	glClearColor(0.0f, 0.04f, 0.06f, 1.0f);

	glfwShowWindow(glWindow);
	glfwFocusWindow(glWindow);

	glInitialized = true;
	return *this;
}

void window_size_callback(GLFWwindow* glwindow, int width, int height)
{
	Window* window = (Window*)glfwGetWindowUserPointer(glwindow);
	window->resize(width, height);
	window->resized = true;
}

void Window::build()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	switch (displayMode)
	{
		default:
		{
			glfwWindowHint(GLFW_RESIZABLE, resizable);
			glWindow = glfwCreateWindow(width, height, title, NULL, NULL);
			break;
		}
		case DISPLAY_WINDOWED_FULLSCREEN:
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glWindow = glfwCreateWindow(mode->width, mode->height, title, glfwGetPrimaryMonitor(), NULL);
			break;
		}
		case DISPLAY_FULLSCREEN:
		{
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
			glWindow = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
			break;
		}
	}

	if (!glWindow)
		std::cout << "Error! : Failed to generate GLFW Window!" << std::endl;

	glfwMakeContextCurrent(glWindow);
	glfwSetWindowUserPointer(glWindow, this);
}

void Window::rebuild()
{
	dispose();
	build();
}

void Window::dispose()
{
	glfwDestroyWindow(glWindow);
}

void Window::clear()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
	resized = false;
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "Internal OpenGL Error! (Unknown Source): " << error << std::endl;

	glfwPollEvents();
	glfwSwapBuffers(glWindow);
}

Window& Window::show()
{
	glfwShowWindow(glWindow);
	return *this;
}

Window& Window::hide()
{
	glfwHideWindow(glWindow);
	return *this;
}

Window& Window::focus()
{
	glfwFocusWindow(glWindow);
	return *this;
}

Window& Window::center()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	setPosition((mode->width / 2) - (width / 2), (mode->height / 2) - (height / 2));
	return *this;
}

Window& Window::resize(const int width, const int height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(glWindow, width, height);
	return *this;
}

Window& Window::setTitle(char* title)
{
	this->title = title;
	glfwSetWindowTitle(glWindow, title);
	return *this;
}

Window& Window::setPosition(const int x, const int y)
{
	glfwSetWindowPos(glWindow, x, y);
	return *this;
}

Window& Window::setDisplay(const int width, const int height, const int displayMode)
{
	resize(width, height);
	setDisplayMode(displayMode);
	return *this;
}

Window& Window::setDisplayMode(const int displayMode)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	switch (displayMode)
	{
		default:
		{
			glfwSetWindowMonitor(glWindow, NULL, (mode->width / 2) - (width / 2), (mode->height / 2) - (height / 2), width, height, mode->refreshRate);
			break;
		}
		case DISPLAY_WINDOWED_FULLSCREEN:
		{
			this->width = mode->width;
			this->height = mode->height;
			glfwSetWindowMonitor(glWindow, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
			break;
		}
		case DISPLAY_FULLSCREEN:
		{
			this->width = width;
			this->height = height;
			glfwSetWindowMonitor(glWindow, glfwGetPrimaryMonitor(), 0, 0, width, height, mode->refreshRate);
			break;
		}
	}
	return *this;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(glWindow) == GL_TRUE ? true : false;
}

bool Window::isResizable() const
{
	return resizable;
}

bool Window::wasResized() const
{
	return resized;
}