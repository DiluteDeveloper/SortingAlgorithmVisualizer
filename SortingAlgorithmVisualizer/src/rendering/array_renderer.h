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
	std::vector<unsigned int> indices;
	unsigned int VAO = 0;

	std::vector<uint16_t>& arrayObj;
	unsigned int heightComplexity = 250;
public:

	RenderOptions rOptions;
	ArrayRenderer(std::vector<uint16_t>& arrayObj, uint16_t heightComplexity) : 
		arrayObj(arrayObj), heightComplexity(heightComplexity) { updateMesh(); }

	void updateMesh();
	void render();

	void swap(uint16_t a, uint16_t b);
};
