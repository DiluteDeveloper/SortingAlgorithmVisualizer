#include "array_mesh.h"

#include <glad/glad.h>

void ArrayMesh2D::generateMesh(std::vector<float> sArray) {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vBuffer);
	vertices.clear();

	float horiScale = 2.0f / static_cast<float>(sArray.size()); // Size of each element+distancetonextelement to be able to fit it all on screen comfortably

	float vertScale = (1.0f / (sArray.size() + 1)) * 2.0f;

	float smoothVal = 0;

	if (renderMode == ArrayMeshRenderMode::HARD)
		smoothVal = vertScale;
	
	std::vector<unsigned int> indices;
	for (size_t i = 0; i < sArray.size(); i++)
	{



		float blockX = (i * horiScale) - 1;
		float marginX = ((i * horiScale) + horiScale) - 1;
		vertices.push_back({ {blockX, -1} }); // bottom left
		vertices.push_back({ {marginX, -1} }); // bottom right
		vertices.push_back({ {marginX, ((vertScale * sArray[i]) - 1) + vertScale}}); // top right
		vertices.push_back({ {blockX, ((vertScale * sArray[i]) - 1) + smoothVal} }); // top left

		indices.push_back((i * 4) + 0);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 1);
		indices.push_back((i * 4) + 3);
		indices.push_back((i * 4) + 2);
		indices.push_back((i * 4) + 0);
	}
	indicesLen = indices.size();

	glCreateBuffers(1, &vBuffer);
	glNamedBufferStorage(vBuffer, sizeof(Vertex2D) * vertices.size(), &vertices[0], GL_DYNAMIC_STORAGE_BIT);

	unsigned int iBuffer = 0;
	glCreateBuffers(1, &iBuffer);
	glNamedBufferStorage(iBuffer, sizeof(unsigned int) * indicesLen, &indices[0], GL_MAP_READ_BIT);

	glCreateVertexArrays(1, &VAO);

	glVertexArrayVertexBuffer(VAO, 0, vBuffer, 0, sizeof(Vertex2D));
	glVertexArrayElementBuffer(VAO, iBuffer);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);

	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, position));
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, colour));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);

	//glDeleteBuffers(1, &iBuffer);
}
void ArrayMesh2D::comparison(const ComparisonData& cd) {

	if (cd.status ==SwapStatus::SWAP) {
		float y3 = vertices[(cd.a * 4) + 3].position.y;
		float y2 = vertices[(cd.a * 4) + 2].position.y;
		vertices[(cd.a * 4) + 2].position.y = vertices[(cd.b * 4) + 2].position.y;
		vertices[(cd.a * 4) + 3].position.y = vertices[(cd.b * 4) + 3].position.y;
		vertices[(cd.b * 4) + 2].position.y = y2;
		vertices[(cd.b * 4) + 3].position.y = y3;

	}
	else if (cd.status == SwapStatus::DONE) {
		glNamedBufferSubData(vBuffer, 0, sizeof(Vertex2D) * vertices.size(), &vertices[0]);
		return;
	}

	if (cd.paintStatus) {
		if (cd.status == SwapStatus::SWAP) {
			vertices[(cd.c * 4)].colour = glm::vec3(0.0f, 1.0f, 0.0f);
			vertices[(cd.c * 4) + 1].colour = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			vertices[(cd.c * 4)].colour = glm::vec3(0.0f, 0.5f, 0.5f);
			vertices[(cd.c * 4) + 1].colour = glm::vec3(0.0f, 0.5f, 0.5f);
		}


		vertices[(cd.c * 4) + 2].colour = glm::vec3(0.0f, 0.5f, 0.5f);
		vertices[(cd.c * 4) + 3].colour = glm::vec3(0.0f, 0.5f, 0.5f);
	}

	if (cd.status == SwapStatus::SWAP) {
		vertices[(cd.b * 4)].colour = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[(cd.b * 4) + 1].colour = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		vertices[(cd.b * 4)].colour = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[(cd.b * 4) + 1].colour = glm::vec3(1.0f, 0.0f, 0.0f);
	}

	vertices[(cd.b * 4) + 2].colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices[(cd.b * 4) + 3].colour = glm::vec3(1.0f, 0.0f, 0.0f);

	if (cd.status == SwapStatus::SWAP) {
		vertices[(cd.a * 4)].colour = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[(cd.a * 4) + 1].colour = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		vertices[(cd.a * 4)].colour = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[(cd.a * 4) + 1].colour = glm::vec3(0.0f, 0.0f, 1.0f);
	}

	vertices[(cd.a * 4) + 2].colour = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[(cd.a * 4) + 3].colour = glm::vec3(0.0f, 0.0f, 1.0f);

	glNamedBufferSubData(vBuffer, 0, sizeof(Vertex2D) * vertices.size(), &vertices[0]);

	if (cd.paintStatus) {
		vertices[(cd.c * 4)].colour = glm::vec3(1.0f, 1.0f, 1.0f);
		vertices[(cd.c * 4) + 1].colour = glm::vec3(1.0f, 1.0f, 1.0f);
		vertices[(cd.c * 4) + 2].colour = glm::vec3(1.0f, 1.0f, 1.0f);
		vertices[(cd.c * 4) + 3].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	vertices[(cd.b * 4)].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.b * 4) + 1].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.b * 4) + 2].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.b * 4) + 3].colour = glm::vec3(1.0f, 1.0f, 1.0f);

	vertices[(cd.a * 4)].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.a * 4) + 1].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.a * 4) + 2].colour = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[(cd.a * 4) + 3].colour = glm::vec3(1.0f, 1.0f, 1.0f);
}