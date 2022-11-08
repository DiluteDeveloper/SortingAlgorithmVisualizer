#pragma once

#include <glm/glm.hpp>
#include <vector>

struct RenderOptions {

	float maxRight = 0.9f;
	float maxLeft = -0.5f;
	float maxHeight = 0.5f;
	float bottomHeight = -0.5f;
};


class ArrayRenderer {
	std::vector<glm::fvec2> vertices;

	unsigned int buffers[2] = {0,0};

	std::vector<unsigned int>& arrayObj;
	unsigned int heightComplexity = 250;

	std::vector<unsigned int> indices;

	unsigned int VAO = 0;
public:

	RenderOptions ro;
	ArrayRenderer(std::vector<unsigned int>& array, unsigned int heightComplexity) : 
		arrayObj(array), heightComplexity(heightComplexity) { updateMesh(); }

	void updateMesh();
	void render();

	void swap(unsigned int a, unsigned int b);
};
