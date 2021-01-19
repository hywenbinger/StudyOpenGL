#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int width = 800;
int height = 600;

// 按下ESC键，关闭窗口
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// 顶点数据
float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

// 索引数据，注意索引从0开始
// 注意：逆时针绘制的在正面，顺时针绘制的在背面
unsigned int indices[] = { 
	0, 3, 1, // 第一个三角形
	1, 3, 2  // 第二个三角形
};

// 顶点着色器
const char* vertexShaderSource =
"#version 330 core  \n"
"layout(location = 6) in vec3 aPos;  \n"
"void main(){  \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}  \n";

// 片段着色器
const char* fragmentShaderSource =
"#version 330 core  \n"
"out vec4 FragColor;  \n"
"void main() {  \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}  \n";

// 主函数
int main()
{
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

	// 打开面剔除功能(默认两面都是绘制的)
	glEnable(GL_CULL_FACE); 
	// 剔除背面
	glCullFace(GL_BACK);

	// 线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	---------------------重点----------开始---------------------
	*/

	// 生成一个【VAO】对象
	unsigned int VAO; // 等价于：unsigned int VAO[1];
	glGenVertexArrays(1, &VAO); // 等价于：glGenVertexArrays(1, VAO);
	// 绑定VAO
	glBindVertexArray(VAO);

	// 生成一个【VBO】对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// VBO绑定到ARRAY_BUFFER上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 把顶点数据复制到VBO中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 生成一个【EBO】对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	// EBO绑定到ELEMENT_ARRAY_BUFFER上
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 把索引数据复制到EBO中 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 至此，已经把顶点数据和索引数据储存在显卡的内存中，分别用VBO和EBO管理
	// 下面会创建一个顶点和片段着色器来真正处理这些数据

	// 生成【顶点着色器】对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 把【顶点着色器源码】附加到顶点着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译顶点着色器
	glCompileShader(vertexShader);

	// 生成【片段着色器】对象
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 把【片段着色器源码】附加到片段着色器对象上
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);

	// 至此，两个着色器都编译好了
	// 下面会把两个着色器对象链接到一个用来渲染的着色器程序(Shader Program)中

	// 创建【着色器程序】对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// 把之前编译的着色器附加到程序对象上
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接着色器程序对象
	glLinkProgram(shaderProgram);
	// 激活着色器程序对象
	glUseProgram(shaderProgram);

	// 把着色器对象链接到着色器程序对象以后，记得删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 至此，已经把输入顶点数据发送给了GPU，并指示了GPU如何在顶点和片段着色器中处理它
	// 但目前OpenGL还不知道该如何解释内存中的顶点数据，以及该如何将顶点数据链接到顶点着色器的属性上
	// 所以，必须在渲染前指定OpenGL该如何解释顶点数据

	// 告诉OpenGL该如何解析顶点数据，即设置顶点属性指针
	// 第一个参数对应 vertexShaderSource 中的 layout
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 启用索引是6的【顶点属性】，顶点属性默认是禁用的
	glEnableVertexAttribArray(6);

	/*
	---------------------重点----------结束---------------------
	*/

	// 创建一个渲染循环（Render Loop）
	while (!glfwWindowShouldClose(window)) {
		// 处理输入
		processInput(window);

		// 渲染
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); // 清空屏幕颜色缓冲

		/*
		---------------------绘制三角形----------开始---------------------
		*/
		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO); 
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		/*
		---------------------绘制三角形----------结束---------------------
		*/

		// 检查并调用事件，交换缓冲
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 释放资源
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}