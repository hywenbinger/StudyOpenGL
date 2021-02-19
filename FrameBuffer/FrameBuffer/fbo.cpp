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
float vertices2[] = {
	//	��������               ��������
		 1.0f, 1.0f,   1.0f, 1.0f,   // ����
		 1.0f, 0.5f,   1.0f, 0.0f,   // ����
		 0.5f, 0.5f,   0.0f, 0.0f,   // ����
		 0.5f, 1.0f,   0.0f, 1.0f    // ����
};

// ��������
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

// ��������
unsigned int indices2[] = {
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

	// �����޳�
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ���м������
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
	Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	shader->use();
	int textureIndex11 = 2;
	unsigned int textureID11 = loadTexture("container.jpg");
	glUniform1i(glGetUniformLocation(shader->ID, "texture11"), textureIndex11);
	int textureIndex12 = 7;
	unsigned int textureID12 = loadTexture("awesomeface.png");
	glUniform1i(glGetUniformLocation(shader->ID, "texture12"), textureIndex12);

	// ���Ͻǵ�����
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	unsigned int EBO2;
	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	Shader* shader2 = new Shader("vertexSource2.vert", "fragmentSource2.frag");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	shader2->use();
	int textureIndex21 = 0;
	glUniform1i(glGetUniformLocation(shader2->ID, "texture21"), textureIndex21);

	// 1.����һ��֡���壬����
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// 2.Ϊ֡���崴��һ��������
	unsigned int texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	// ע�⣺����������data����������NULL����˽����������ڴ��û�������������������������Ⱦ��֡����֮�������С�
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// 3.�����������ӵ���ǰ�󶨵�֡�������
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	// 4.���֡�����Ƿ�����
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		cout << "Framebuffer is not complete!" << endl;
	}
	else
	{
		cout << "Framebuffer is complete!" << endl;
	}
	// 5.���֡���壬��֤����������Ⱦ����Ĭ�ϵ�֡���塿��
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// 6.��֡���壬������������Ⱦ����֡����Ļ��塿�ж����ǡ�Ĭ�ϵ�֡���塿��
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0 + textureIndex11);
		glBindTexture(GL_TEXTURE_2D, textureID11);
		glActiveTexture(GL_TEXTURE0 + textureIndex12);
		glBindTexture(GL_TEXTURE_2D, textureID12);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 7.���֡���壬��֤����������Ⱦ����Ĭ�ϵ�֡���塿��
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader2->use();
		glBindVertexArray(VAO2);
		glActiveTexture(GL_TEXTURE0 + textureIndex21);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ��չ����Ȼ��������������Ⱦ����һ�������ϣ���ô�Ϳ��Լ򵥵�ͨ���޸��������ݴ�����һЩ�ǳ�����˼��Ч����

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

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