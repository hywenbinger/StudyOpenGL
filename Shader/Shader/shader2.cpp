/*
��Ӷ�����ɫ����
*/

//#define GLEW_STATIC
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
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
//	// ����                // ��ɫ
//	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
//	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
//};
//
//// ��������
//unsigned int indices[] = {
//	0, 1, 2,
//	0, 2, 3
//};
//
//// ������ɫ��
//const char* vertexShaderSource =
//"#version 330 core  \n"
//"layout(location = 6) in vec3 aPos;   //λ�ñ���������λ��ֵΪ6  \n"
//"layout(location = 7) in vec3 aColor; //��ɫ����������λ��ֵΪ7  \n"
//"out vec3 ourColor; //ΪƬ����ɫ��ָ��һ����ɫ���  \n"
//"void main(){  \n"
//"	gl_Position = vec4(aPos, 1.0);  \n"
//"	ourColor = aColor; //��ourColor����Ϊ�Ӷ�����������õ���������ɫ  \n"
//"}  \n";
//
//// Ƭ����ɫ��
//const char* fragmentShaderSource =
//"#version 330 core  \n"
//"out vec4 fragColor;  \n"
//"in vec3 ourColor; //�Ӷ�����ɫ����������ɫ����  \n"
//"void main() {  \n"
//"	fragColor = vec4(ourColor, 1.0);  \n"
//"}  \n";
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
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glUseProgram(shaderProgram);
//
//	// position attribute
//	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(6);
//	// color attribute
//	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(7);
//
//
//	// ����һ����Ⱦѭ����Render Loop��
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ������ɫ��
//		glUseProgram(shaderProgram);
//		// ����
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteBuffers(1, &VBO);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//
//	return 0;
//}