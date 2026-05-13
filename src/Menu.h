#pragma once

#include <iostream>
#include <print>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include "Scanner.h"

class Menu
{
	private:
		Scanner sc;
		void renderToolbar();
		void renderResults();
		void renderSelected();

		GLFWwindow* window;

		int currentPage = 0;
		int selectedIndex = -1;
		int selectedType = 0;
		int scanValue = 0;
		static const int perPage = 20;
		char searchInput[32];
		char editInput[32];

	public:
	Menu();
	~Menu();
	bool update();
};
