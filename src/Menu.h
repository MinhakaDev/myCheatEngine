#pragma once

#include <iostream>
#include <print>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

class Menu
{
	private:
		char type;
		GLFWwindow* window;

	public:
	Menu();
	~Menu();
	bool update();
};
