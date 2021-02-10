#define GLEW_STATIC

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

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
	//	顶点坐标               纹理坐标
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上
};

// 索引数据
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

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

	glViewport(0, 0, width, height);

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
	Shader* myShader = new Shader("vertexSource2.vert", "fragmentSource2.frag");

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// uv attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 第一个纹理
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE3); // 激活纹理单元3
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load container.jpg" << endl;
	}
	stbi_image_free(data);

	// 第二个纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE6); // 激活纹理单元6
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load awesomeface.png" << endl;
	}
	stbi_image_free(data);

	// 设置uniform变量之前一定要激活着色器程序!
	myShader->use();

	// 设置着色器中的sample属于哪个纹理单元
	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), 3);
	glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), 6);

	//矩阵变换
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(-0.2f, 0, 0)); //位移
	//trans = glm::rotate(trans, glm::radians(30.0f), glm::vec3(0.0, 0.0, 1.0)); //旋转
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); //缩放

	// 把矩阵数据发送给为着色器
	//unsigned int transformLoc = glGetUniformLocation(myShader->ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绑定并绘制
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, texture2);

		myShader->use();

		// 通过矩阵变换，实现动画(先旋转，再位移)
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.2f, 0.2f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		unsigned int transformLoc = glGetUniformLocation(myShader->ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		// 注意：要记住的是前面的例子中我们可以在任何地方声明变换矩阵，
		//      但是现在我们必须在每一次迭代中创建它，从而保证我们能够不断更新旋转角度。
		//      这也就意味着我们不得不在每次游戏循环的迭代中重新创建变换矩阵。

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