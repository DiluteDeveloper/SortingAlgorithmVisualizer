#pragma once

#include <glm/glm.hpp>

struct Vertex2D {
	glm::fvec2 position = glm::fvec2(0.0f);
	glm::fvec3 colour = glm::fvec3(1.0f);

	Vertex2D(glm::fvec2 position) : position(position) {};
	Vertex2D(glm::fvec2 position, glm::fvec3 colour) : position(position), colour(colour) {};
	Vertex2D() = default;
};
