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

// 顶点数据
float vertices2[] = {
	//	顶点坐标               纹理坐标
		 1.0f, 1.0f,   1.0f, 1.0f,   // 右上
		 1.0f, 0.5f,   1.0f, 0.0f,   // 右下
		 0.5f, 0.5f,   0.0f, 0.0f,   // 左下
		 0.5f, 1.0f,   0.0f, 1.0f    // 左上
};

// 索引数据
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

// 索引数据
unsigned int indices2[] = {
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

	// 背面剔除
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// 线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 正中间的纹理
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
	shader->use();
	int textureIndex11 = 2;
	unsigned int textureID11 = loadTexture("container.jpg");
	glUniform1i(glGetUniformLocation(shader->ID, "texture11"), textureIndex11);
	int textureIndex12 = 7;
	unsigned int textureID12 = loadTexture("awesomeface.png");
	glUniform1i(glGetUniformLocation(shader->ID, "texture12"), textureIndex12);

	// 右上角的纹理
	unsigned int VAO2;
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	unsigned int VBO2;
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	unsigned int EBO2;
	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	Shader* shader2 = new Shader("vertexSource2.vert", "fragmentSource2.frag");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	shader2->use();
	int textureIndex21 = 0;
	glUniform1i(glGetUniformLocation(shader2->ID, "texture21"), textureIndex21);

	// 1.创建一个帧缓冲，并绑定
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// 2.为帧缓冲创建一个纹理附件
	unsigned int texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	// 注意：这里给纹理的data参数传递了NULL，因此仅仅分配了内存而没有填充它；填充这个纹理将会在渲染到帧缓冲之后来进行。
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// 3.将纹理附件附加到当前绑定的帧缓冲对象
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	// 4.检查帧缓冲是否完整
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		cout << "Framebuffer is not complete!" << endl;
	}
	else
	{
		cout << "Framebuffer is complete!" << endl;
	}
	// 5.解绑帧缓冲，保证后续操作渲染到【默认的帧缓冲】上
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// 6.绑定帧缓冲，后续操作会渲染到【帧缓冲的缓冲】中而不是【默认的帧缓冲】中
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0 + textureIndex11);
		glBindTexture(GL_TEXTURE_2D, textureID11);
		glActiveTexture(GL_TEXTURE0 + textureIndex12);
		glBindTexture(GL_TEXTURE_2D, textureID12);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 7.解绑帧缓冲，保证后续操作渲染到【默认的帧缓冲】中
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader2->use();
		glBindVertexArray(VAO2);
		glActiveTexture(GL_TEXTURE0 + textureIndex21);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 延展：既然整个场景都被渲染到了一个纹理上，那么就可以简单地通过修改纹理数据创建出一些非常有意思的效果。

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);

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