#pragma once

#include <vector>

#include "vertex.h"

#include "array/sorts/sort_system.h"

// Want to make reusable at some point
class ArrayMesh2D {
	friend class Renderer2D;

	/* Needed for swapping */
	std::vector<Vertex2D> vertices;
	unsigned int vBuffer = 0; 

	/* Needed for rendering */
	unsigned int VAO = 0;
	uint16_t indicesLen = 0;
public:

	enum class ArrayMeshRenderMode {
		HARD,
		SMOOTH
	};

	ArrayMeshRenderMode renderMode = ArrayMeshRenderMode::HARD;

	ArrayMesh2D() = default;

	void generateMesh(std::vector<float> sArray);

	// Swaps vertex positions (for now)
	void comparison(const ComparisonData& c);
};
