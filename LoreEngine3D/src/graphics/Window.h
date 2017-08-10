#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#define DISPLAY_WINDOWED			0
#define DISPLAY_FULLSCREEN			1
#define DISPLAY_WINDOWED_FULLSCREEN	2

class Window
{
private:

	GLFWwindow* glWindow;
	short displayMode;
	bool vsync;
	bool resizable;
	bool resized;

	char* title;
	int width;
	int height;

	static bool glInitialized;

public:

	Window(char* title, const int width, const int height, const int displayMode = DISPLAY_WINDOWED, const bool vsync = false, const bool resizable = true);
	~Window();

	Window& create();
	void rebuild();
	void dispose();

	void clear();
	void update();

	Window& show();
	Window& hide();
	Window& focus();
	Window& center();

	Window& resize(const int width, const int height);
	Window& setTitle(char* title);
	Window& setPosition(const int x, const int y);
	Window& setDisplay(const int width, const int height, const int displayMode);
	Window& setDisplayMode(const int displayMode);

	bool shouldClose() const;
	bool isResizable() const;
	
	bool wasResized() const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	inline const char* getTitle() const { return title; }

private:

	void friend glErrorCallback(int error, const char* description);
	void friend window_size_callback(GLFWwindow* window, int width, int height);
	void initOpenGL();
	void build();

};