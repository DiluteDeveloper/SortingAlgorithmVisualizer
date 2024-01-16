#pragma once

struct GLFWwindow;

#include <vector>
#include <memory>

#include "array/array_system.h"

class GUISystem {

	unsigned int persistentSize = 50;
	double fpsLimit = 1.0 / 20.0;

	bool sorted = true;
	bool sorting = false;

	bool showSortUI = true;
	bool showMouseDuringSort = true;

	GLFWwindow* window;

	void generationGUI();
	void renderingGUI();
	void sortingGUI();
	void miscGUI();

public:
	GUISystem(GLFWwindow* window);
	void update();

	ArraySystem aSystem;
};
