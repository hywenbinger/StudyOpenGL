#define GLEW_STATIC

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

using namespace std;

int screenWidth = 800;
int screenHeight = 600;

void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// ��������
float vertices[] = {
	//	��������               ��������
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // ����
};

// ��������
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

// ������
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "MyOpenGLWindow", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cout << "Failed to init GLEW" << endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// create and compile Shader
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// uv attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��һ������
	int textureIndex1 = 2;
	unsigned int textureID1 = loadTexture("container.jpg");

	// �ڶ�������
	int textureIndex2 = 7;
	unsigned int textureID2 = loadTexture("awesomeface.png");

	// ����uniform����֮ǰһ��Ҫ������ɫ������!
	myShader->use();

	// ������ɫ���е�sample�����ĸ�����Ԫ
	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), textureIndex1);
	glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), textureIndex2);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0 + textureIndex1); // ��������Ԫ
		glBindTexture(GL_TEXTURE_2D, textureID1); // ������
		glActiveTexture(GL_TEXTURE0 + textureIndex2);
		glBindTexture(GL_TEXTURE_2D, textureID2);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// ��������
void processInput(GLFWwindow* window) {
	// ����ESC�����رմ���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// ��������
unsigned int loadTexture(char const * path) {
	// �����������
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// ����ͼƬ
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		// ������
		glBindTexture(GL_TEXTURE_2D, textureID); 
		// Ϊ��ǰ�󶨵�������������ͼ��
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
		glGenerateMipmap(GL_TEXTURE_2D);
		// Ϊ��ǰ�󶨵��������û��ơ����˷�ʽ
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		cout << "Failed to load " << path << endl;
	}
	stbi_image_free(data);
	return textureID;
}