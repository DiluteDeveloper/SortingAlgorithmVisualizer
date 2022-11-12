#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "array_mesh.h"

class Renderer2D {

	unsigned int shaderProgram = 0;
public:

	Renderer2D();

	void renderArrayMesh(const ArrayMesh2D& aMesh);
};
