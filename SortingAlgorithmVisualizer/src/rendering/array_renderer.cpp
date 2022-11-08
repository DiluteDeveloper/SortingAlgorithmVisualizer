#include <iostream>
#include <glad/glad.h>

#include "array_renderer.h"

void ArrayRenderer::updateMesh() {

	glDeleteBuffers(2, &buffers[0]);
	glDeleteVertexArrays(1, &VAO);
	indices.clear();
	vertices.clear();

	float horiScale = ((ro.maxRight - ro.maxLeft) / (float)arrayObj.size()); // Size of each element+distancetonextelement to be able to fit it all on screen comfortably
	float vertScale = ((ro.maxHeight - ro.bottomHeight) / heightComplexity); // 100 would be the size of the largest element hypothetically.

	for (size_t i = 0; i < arrayObj.size(); i++)
	{

		float blockX = i * horiScale;
		float marginX = (i * horiScale) + (horiScale / 2);
		vertices.push_back({ ro.maxLeft + blockX, ro.bottomHeight }); // bottom left
		vertices.push_back({ ro.maxLeft + marginX, ro.bottomHeight }); // bottom right
		vertices.push_back({ ro.maxLeft + marginX, ro.bottomHeight + (vertScale * arrayObj[i])}); // top right
		vertices.push_back({ ro.maxLeft + blockX, ro.bottomHeight + (vertScale * arrayObj[i]) }); // top left

		indices.push_back((i * 4) + 0);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 1);
		indices.push_back((i * 4) + 3);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 0);
	}

	glCreateBuffers(2, &buffers[0]);
	glNamedBufferStorage(buffers[0], sizeof(glm::fvec2) * vertices.size(), &vertices[0], GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &buffers[1]);
	glNamedBufferStorage(buffers[1], sizeof(unsigned int) * indices.size(), &indices[0], GL_MAP_READ_BIT);

	glCreateVertexArrays(1, &VAO);

	glVertexArrayVertexBuffer(VAO, 0, buffers[0], 0, sizeof(glm::fvec2));
	glVertexArrayElementBuffer(VAO, buffers[1]);

	glEnableVertexArrayAttrib(VAO, 0);

	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(VAO, 0, 0);
}

void ArrayRenderer::render() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void ArrayRenderer::swap(unsigned int a, unsigned int b) {
	vertices[(a * 4 + 2)].y = vertices[(b * 4 + 2)].y;
	vertices[(b * 4 + 2)].y = vertices[(a * 4 + 3)].y;
	float y1 = vertices[(a * 4 + 3)].y;
	vertices[(a * 4 + 3)].y = vertices[(b * 4 + 3)].y;
	vertices[(b * 4 + 3)].y = y1;

	glNamedBufferSubData(buffers[0], 0, sizeof(glm::fvec2) * vertices.size(), &vertices[0]);
}