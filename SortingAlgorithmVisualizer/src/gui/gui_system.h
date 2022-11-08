#pragma once

struct GLFWwindow;

#include <vector>
#include <memory>

#include "array/array_system.h"

class GUISystem {

	unsigned int persistentSize = 50;
	unsigned int persistentHeightComplexity = 100;
	RenderOptions persistentRO;


	bool sorting = false;
	double sortStartTime = 0.0f;
	double sortFinishTime = 0.0f;

	GLFWwindow* window;

	void generationGUI();
	void renderingGUI();
	void sortingGUI();
	void miscGUI();

public:
	GUISystem(GLFWwindow* window);
	void update();

	std::unique_ptr<ArraySystem> aSystem;
};
