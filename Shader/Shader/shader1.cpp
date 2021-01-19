/*
�˽�Shader
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
//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	0.5f, -0.5f, 0.0f,  // ���½�
//	-0.5f, -0.5f, 0.0f, // ���½�
//};
//
//// ��������
//unsigned int indices[] = {
//	0, 2, 1
//};
//
//// ������ɫ��
//const char* vertexShaderSource =
//"#version 330 core  \n"
//"layout(location = 6) in vec3 aPos; //�������Ե�λ����6  \n"
//"out vec4 vertexColor; //ΪƬ����ɫ��ָ��һ����ɫ���  \n"
//"void main(){  \n"
//"	gl_Position = vec4(aPos, 1.0);  \n"
//"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);  \n"
//"}  \n";
//
//// Ƭ����ɫ��
//const char* fragmentShaderSource =
//"#version 330 core  \n"
//"out vec4 FragColor;  \n"
//"in vec4 vertexColor; //�Ӷ�����ɫ���������������(������ͬ��������ͬ)  \n"
//"uniform vec4 ourColor; //����һ��Uniform����  \n"
//"void main() {  \n"
//"	FragColor = ourColor;  \n"
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
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
//
//	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(6);
//
//	// ����һ����Ⱦѭ����Render Loop��
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//
//		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ������ɫ��
//		glUseProgram(shaderProgram);
//
//		float timeValue = glfwGetTime();
//		float colorValue = sin(timeValue) / 2.0f + 0.5f;
//		// ��ȡuniform������/λ��ֵ������-1�ʹ���δ�ҵ�
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//		// ����uniformֵ��ע�⣺������glUseProgram������
//		glUniform4f(vertexColorLocation, colorValue, 0.0f, 0.0f, 1.0f);
//
//		// ����
//		glBindVertexArray(VAO);
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//		
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//
//	return 0;
//}