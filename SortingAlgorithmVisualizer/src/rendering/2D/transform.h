#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Transform2D {
	glm::fvec2 position;
	float rotation;
	glm::fvec2 scale;



	Transform2D(glm::fvec2 position = glm::fvec2(0.0f), float rotation =(0.0f), glm::fvec2 scale = glm::fvec2(1.0f))
		: position{ position }, rotation{ rotation }, scale{ scale } {};

	[[nodiscard]] glm::fmat4 getMat4() const {
		glm::fmat4 ret(1.0f);
		ret = glm::translate(ret, glm::vec3(position.x, position.y, 0));
		ret = glm::rotate(ret, glm::radians(rotation), glm::fvec3(0, 0, 1));
		ret = glm::scale(ret, glm::vec3(scale.x, scale.y, 1));
		return ret;
	}

};
