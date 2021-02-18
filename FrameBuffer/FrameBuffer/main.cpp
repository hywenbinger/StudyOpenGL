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
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// uv attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 第一个纹理
	int textureIndex1 = 2;
	unsigned int textureID1 = loadTexture("container.jpg");

	// 第二个纹理
	int textureIndex2 = 7;
	unsigned int textureID2 = loadTexture("awesomeface.png");

	// 设置uniform变量之前一定要激活着色器程序!
	myShader->use();

	// 设置着色器中的sample属于哪个纹理单元
	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), textureIndex1);
	glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), textureIndex2);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0 + textureIndex1); // 激活纹理单元
		glBindTexture(GL_TEXTURE_2D, textureID1); // 绑定纹理
		glActiveTexture(GL_TEXTURE0 + textureIndex2);
		glBindTexture(GL_TEXTURE_2D, textureID2);

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

// 按键处理
void processInput(GLFWwindow* window) {
	// 按下ESC键，关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// 加载纹理
unsigned int loadTexture(char const * path) {
	// 生成纹理对象
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// 加载图片
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

		// 绑定纹理
		glBindTexture(GL_TEXTURE_2D, textureID); 
		// 为当前绑定的纹理附加上纹理图像
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// 为当前绑定的纹理自动生成所有需要的多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
		// 为当前绑定的纹理设置环绕、过滤方式
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