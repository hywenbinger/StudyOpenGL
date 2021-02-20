#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	// 保证ifstream对象可以抛出异常
	vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		// 打开文件
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		// 判断文件是否打开
		if (!vertexFile.is_open() || !fragmentFile.is_open()) {
			throw exception("Open file error!!!");
		}
		stringstream vertextSStream;
		stringstream fragmentSStream;
		// 读取文件的缓冲内容到数据流中
		vertextSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();
		// 关闭文件处理器
		vertexFile.close();
		fragmentFile.close();
		// 转换数据流到string
		vertexString = vertextSStream.str();
		fragmentString = fragmentSStream.str();
		// string转成最终结果
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		//cout << vertexSource << endl;
		//cout << fragmentSource << endl;

		// 编译Shader
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int id, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
}

