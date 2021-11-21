#include "glew_shader.hpp"

#include <iostream>


GlewShader::GlewShader(const char* source, GlewShaderType shaderType)
{
	_shader = glCreateShader(GetNativeShaderType(shaderType));
	glShaderSource(_shader, 1, &source, NULL); // 1 string is used
	glCompileShader(_shader);

	// Check if shader was compiled properly
	GLint success = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	_isCompiled = success == GL_TRUE;

	// TODO: remove
	GLchar infoLog[512];
	if (!_isCompiled)
	{
		glGetShaderInfoLog(_shader, 512, NULL, infoLog);
		std::cout << "SHADER COMPILATION FAILED\n" << infoLog << std::endl;
		std::cout << source << std::endl;
	}
}

GlewShader::~GlewShader()
{
	glDeleteShader(_shader);
}


GLuint GlewShader::GetId() const
{
	return _shader;
}

bool GlewShader::IsCompiled() const
{
	return _isCompiled;
}


OpResult GlewShader::LoadFromFile(const char* path, GlewShaderType shaderType, GlewShader** shader)
{
	AbstractFileSystem* fileSystem = Container::GetFileSystem();
	std::string source;
	if (fileSystem->ReadString(path, source) == FAILURE)
	{
		return FAILURE;
	}
	else
	{
		*shader = new GlewShader(source.c_str(), shaderType);
		return SUCCESS;
	}
}


GLuint GlewShader::GetNativeShaderType(GlewShaderType shaderType)
{
	switch (shaderType)
	{
	case GlewShaderType::Vertex:
		return GL_VERTEX_SHADER;
	case GlewShaderType::Geometry:
		return GL_GEOMETRY_SHADER;
	case GlewShaderType::Fragment:
		return GL_FRAGMENT_SHADER;
	}
}
