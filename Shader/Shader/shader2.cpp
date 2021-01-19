/*
添加顶点颜色属性
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
//// 按下ESC键，关闭窗口
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// 顶点数据
//float vertices[] = {
//	// 顶点                // 颜色
//	 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
//	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f
//};
//
//// 索引数据
//unsigned int indices[] = {
//	0, 1, 2,
//	0, 2, 3
//};
//
//// 顶点着色器
//const char* vertexShaderSource =
//"#version 330 core  \n"
//"layout(location = 6) in vec3 aPos;   //位置变量的属性位置值为6  \n"
//"layout(location = 7) in vec3 aColor; //颜色变量的属性位置值为7  \n"
//"out vec3 ourColor; //为片段着色器指定一个颜色输出  \n"
//"void main(){  \n"
//"	gl_Position = vec4(aPos, 1.0);  \n"
//"	ourColor = aColor; //将ourColor设置为从顶点数据那里得到的输入颜色  \n"
//"}  \n";
//
//// 片段着色器
//const char* fragmentShaderSource =
//"#version 330 core  \n"
//"out vec4 fragColor;  \n"
//"in vec3 ourColor; //从顶点着色器传来的颜色输入  \n"
//"void main() {  \n"
//"	fragColor = vec4(ourColor, 1.0);  \n"
//"}  \n";
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
//	// 创建一个渲染循环（Render Loop）
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// 激活着色器
//		glUseProgram(shaderProgram);
//		// 绘制
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