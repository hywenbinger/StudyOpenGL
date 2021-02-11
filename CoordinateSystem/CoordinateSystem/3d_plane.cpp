//#define GLEW_STATIC
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//
//using namespace std;
//
//int screenWidth = 800;
//int screenHeight = 600;
//
//// 按下ESC键，关闭窗口
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// 顶点数据
//float vertices[] = {
//	//	顶点坐标               纹理坐标
//		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上
//};
//
//// 索引数据
//unsigned int indices[] = {
//	0, 2, 1,
//	0, 3, 2
//};
//
//// 主函数
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Open GLFW Window
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "MyOpenGLWindow", NULL, NULL);
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
//	glViewport(0, 0, screenWidth, screenHeight);
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
//	Shader* myShader = new Shader("vertexSource_plane.vert", "fragmentSource.frag");
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// uv attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// 第一个纹理
//	unsigned int texture1;
//	glGenTextures(1, &texture1);
//	glActiveTexture(GL_TEXTURE3); // 激活纹理单元3
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		cout << "Failed to load container.jpg" << endl;
//	}
//	stbi_image_free(data);
//
//	// 第二个纹理
//	unsigned int texture2;
//	glGenTextures(1, &texture2);
//	glActiveTexture(GL_TEXTURE6); // 激活纹理单元6
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		cout << "Failed to load awesomeface.png" << endl;
//	}
//	stbi_image_free(data);
//
//	// 设置uniform变量之前一定要激活着色器程序!
//	myShader->use();
//
//	// 设置着色器中的sample属于哪个纹理单元
//	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), 3);
//	glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), 6);
//
//	// 模型矩阵
//	glm::mat4 modelMat;
//	modelMat = glm::rotate(modelMat, glm::radians(-60.0f), glm::vec3(1.0, 0.0, 0.0));
//	glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"),
//		1, GL_FALSE, glm::value_ptr(modelMat));
//
//	// 观察矩阵
//	glm::mat4 viewMat;
//	viewMat = glm::translate(viewMat, glm::vec3(0.0, 0.0, -3.0));
//	glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"),
//		1, GL_FALSE, glm::value_ptr(viewMat));
//
//	// 透视矩阵
//	glm::mat4 projectionMat;
//	projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//	glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projectionMat"),
//		1, GL_FALSE, glm::value_ptr(projectionMat));
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// 绑定并绘制
//		glActiveTexture(GL_TEXTURE3);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE6);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		myShader->use();
//
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
//	return 0;
//}