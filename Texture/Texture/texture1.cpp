//#define GLEW_STATIC
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//
//using namespace std;
//
//int width = 800;
//int height = 600;
//
//// ����ESC�����رմ���
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// ��������
//float vertices[] = {
////	����                   ��ɫ                ��������
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};
//
//// ��������
//unsigned int indices[] = {
//	0, 2, 1,
//	0, 3, 2
//};
//
//// ������
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Open GLFW Window
//	GLFWwindow* window = glfwCreateWindow(width, height, "MyOpenGLWindow", NULL, NULL);
//	if (window == NULL) {
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Init GLEW
//	glewExperimental = true;
//	if (glewInit() != GLEW_OK) {
//		cout << "Failed to init GLEW" << endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glViewport(0, 0, width, height);
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// create and compile Shader
//	Shader* myShader = new Shader("vertexSource.vert","fragmentSource.frag");
//
//	// position attribute
//	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(6);
//	// color attribute
//	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(7);
//	// uv attribute
//	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(8);
//
//	// ��������ID������
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glActiveTexture(GL_TEXTURE0); //������ǰ�ȼ�������Ԫ������ԪGL_TEXTURE0Ĭ�����Ǳ�������Կ��Բ�д������
//	glBindTexture(GL_TEXTURE_2D, texture);
//	// Ϊ��ǰ�󶨵������������Wrap Mode��Filter Mode
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// ���ر���ͼƬ
//	int width, height, nrChannels;
//	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// Ϊ��ǰ�󶨵�������󸽼�������ͼ��
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		// ���ɶ༶��������
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		cout << "Failed to load texture" << endl;
//	}
//	// �ͷ�ͼ����ڴ�
//	stbi_image_free(data);
//
//	// ע�⣺���ﲢû�и�Ƭ����ɫ���е�uniform sampler2D��ֵ��OpenGL����ô���������ͼ�ģ�
//	// ������Ϊ������ԪGL_TEXTURE0Ĭ�����Ǳ�������Ե�ʹ��glBindTexture��ʱ�����輤���κ�����Ԫ��Ĭ�ϻḳֵ��Ƭ����ɫ���еĵ�һ��sampler2D��
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ������ɫ��
//		myShader->use();
//
//		// ����
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		//glBindTexture(GL_TEXTURE_2D, 0);
//		//glBindVertexArray(0);
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glDeleteVertexArrays(1, &VAO);
//
//	glfwTerminate();
//
//	return 0;
//}