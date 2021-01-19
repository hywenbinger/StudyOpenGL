#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;

// 按下ESC键，关闭窗口
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	int width = 800;
	int height = 600;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(width, height, "MyOpenGLWindow", NULL, NULL);
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

	// 前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽、高像素值。
	glViewport(0, 0, width, height);

	// 创建一个渲染循环（Render Loop）
	while (!glfwWindowShouldClose(window)){
		// 处理输入
		processInput(window);

		// 渲染
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); // 清空屏幕颜色缓冲

		// glClearColor函数是一个状态设置函数，
		// glClear函数则是一个状态使用的函数，它使用了当前的状态来获取应该清除为什么颜色

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 释放资源
	glfwTerminate();

	return 0;
}