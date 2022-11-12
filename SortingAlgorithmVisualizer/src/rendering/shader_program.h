#pragma once

#include <string>
#include <glad/glad.h>

#include "../io/filestream.h"

unsigned int CreateShader(const std::string& filePath, const int type) {
	const unsigned int shaderID = glCreateShader(type);

	const std::string source(ReadFile(filePath));
	const char* cSource = source.c_str();
	glShaderSource(shaderID, 1, &cSource, nullptr);

	glCompileShader(shaderID);

	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {

		char infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);

		std::cout << infoLog << std::endl;
		throw std::exception();
	}
	return shaderID;
}


unsigned int CreateShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader) {

	const unsigned int ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glValidateProgram(ID);

	int success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);

		std::cout << infoLog << std::endl;
		throw std::exception();
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return ID;


}
/*
void ShaderProgram::BindToContext() const {
	glUseProgram(id);
}

void ShaderProgram::SetUniform4FV(const std::string& name, const glm::fvec4& value) {
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);

}
void ShaderProgram::SetUniform3FV(const std::string& name, const glm::fvec3& value) {
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);

}
void ShaderProgram::SetUniform2FV(const std::string& name, const glm::fvec2& value) {
	glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}

void ShaderProgram::SetUniform1FV(const std::string& name, const float value) {
	glUniform1fv(GetUniformLocation(name), 1, &value);
}


void ShaderProgram::SetUniform4IV(const std::string& name, const glm::ivec4& value) {
	glUniform4iv(GetUniformLocation(name), 1, &value[0]);
}
void ShaderProgram::SetUniform3IV(const std::string& name, const glm::ivec3& value) {
	glUniform3iv(GetUniformLocation(name), 1, &value[0]);
}
void ShaderProgram::SetUniform2IV(const std::string& name, const glm::ivec2& value) {
	glUniform2iv(GetUniformLocation(name), 1, &value[0]);
}
void ShaderProgram::SetUniform1IV(const std::string& name, const int value) {
	glUniform1iv(GetUniformLocation(name), 1, &value);
}

void ShaderProgram::SetUniformMatrix4FV(const std::string& name, const glm::fmat4& value) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::SetUniformMatrix3FV(const std::string& name, const glm::fmat3& value) {
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::SetUniformMatrix2FV(const std::string& name, const glm::fmat2& value) {
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
}
*/