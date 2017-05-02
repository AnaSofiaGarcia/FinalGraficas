#include "Shader.h"

#include "InputFile.h"
#include <iostream>

using namespace std;

Shader::Shader()
{
	_shaderHandle = 0;
}

Shader::~Shader()
{
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(std::string path, GLenum type)
{
	/*InputFile ifile;
	if (!ifile.Read(path)) return;
	std::string source = ifile.GetContents();

	if (_shaderHandle)
		glDeleteShader(_shaderHandle);

	_shaderHandle = glCreateShader(type);

	const GLchar *source_c = (const GLchar*)source.c_str();
	glShaderSource(_shaderHandle, 1, &source_c, nullptr);

	glCompileShader(_shaderHandle);*/

	if (_shaderHandle != 0) {
		glDeleteShader(_shaderHandle);
	}
	InputFile file;
	file.Read(path);
	string vertexShaderSource = file.getContents();
	const GLchar* vertexShaderSourceC = (const GLchar *)vertexShaderSource.c_str();
	_shaderHandle = glCreateShader(type);
	glShaderSource(_shaderHandle, 1, &vertexShaderSourceC, 0);
	glCompileShader(_shaderHandle);
}

GLuint Shader::GetHandle()
{
	return _shaderHandle;
}