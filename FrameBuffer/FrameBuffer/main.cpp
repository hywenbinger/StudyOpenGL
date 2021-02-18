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
float verticesFBO[] = {
	//	��������               ��������
		 1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // ����
		 1.0f, 0.5f, 0.0f,   1.0f, 0.0f,   // ����
		 0.5f, 0.5f, 0.0f,   0.0f, 0.0f,   // ����
		 0.5f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

// ��������
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

// ��������
unsigned int indicesFBO[] = {
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
	int textureIndex1 = 2;
	unsigned int textureID1 = loadTexture("container.jpg");
	int textureIndex2 = 7;
	unsigned int textureID2 = loadTexture("awesomeface.png");
	shader->use();
	glUniform1i(glGetUniformLocation(shader->ID, "texture1"), textureIndex1);
	glUniform1i(glGetUniformLocation(shader->ID, "texture2"), textureIndex2);

	// ���Ͻǵ�����
	unsigned int VAOFBO;
	glGenVertexArrays(1, &VAOFBO);
	glBindVertexArray(VAOFBO);
	unsigned int VBOFBO;
	glGenBuffers(1, &VBOFBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOFBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFBO), verticesFBO, GL_STATIC_DRAW);
	unsigned int EBOFBO;
	glGenBuffers(1, &EBOFBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOFBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesFBO), indicesFBO, GL_STATIC_DRAW);
	Shader* shaderFBO = new Shader("vertexSourceFBO.vert", "fragmentSourceFBO.frag");
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(7);
	int textureIndexFBO = 1;
	unsigned int textureIDFBO = loadTexture("wall.jpg");
	shaderFBO->use();
	glUniform1i(glGetUniformLocation(shaderFBO->ID, "fboTexture"), textureIndexFBO);


	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0 + textureIndex1); 
		glBindTexture(GL_TEXTURE_2D, textureID1); 
		glActiveTexture(GL_TEXTURE0 + textureIndex2);
		glBindTexture(GL_TEXTURE_2D, textureID2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shaderFBO->use();
		glBindVertexArray(VAOFBO);
		glActiveTexture(GL_TEXTURE0 + textureIndexFBO);
		glBindTexture(GL_TEXTURE_2D, textureIDFBO); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAOFBO);
	glDeleteBuffers(1, &VBOFBO);
	glDeleteBuffers(1, &EBOFBO);

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