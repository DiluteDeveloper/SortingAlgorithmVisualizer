#include <iostream>
#include <glad/glad.h>

#include "renderer.h"
#include "rendering/shader_program.h"

// Just creates the vertices. we do all the positioning later so we dont have to fuck around with vertices when swapping
Renderer2D::Renderer2D() {


	unsigned int vertexShader = CreateShader("res/shaders/shader2D.vs", GL_VERTEX_SHADER);
	unsigned int fragmentShader = CreateShader("res/shaders/shader2D.fs", GL_FRAGMENT_SHADER);

	shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
	
	/*glm::ivec2 vertices[] = {
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};

	unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2
	};


	unsigned int buffers[2];
	glCreateBuffers(2, &buffers[0]);
	glNamedBufferStorage(buffers[0], sizeof(glm::ivec2) * 4, &vertices[0], GL_MAP_READ_BIT);

	glNamedBufferStorage(buffers[1], sizeof(unsigned int) * 6, &indices[0], GL_MAP_READ_BIT);

	glCreateVertexArrays(1, &VAO);

	glVertexArrayVertexBuffer(VAO, 0, buffers[0], 0, sizeof(Vertex));
	glVertexArrayElementBuffer(VAO, buffers[1]);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);

	glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, colour));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);*/
}

void Renderer2D::renderArrayMesh(const ArrayMesh2D& aMesh) {

	glUseProgram(shaderProgram);
	glBindVertexArray(aMesh.VAO);
	glDrawElements(GL_TRIANGLES, aMesh.indicesLen, GL_UNSIGNED_INT, nullptr);
}