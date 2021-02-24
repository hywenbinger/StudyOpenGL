//#define GLEW_STATIC
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//#include <string>
//#include <sstream>
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
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//
//float quadVertices[] = {
//	// 位置          // 颜色
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//	 0.05f,  0.05f,  0.0f, 0.0f, 1.0f
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
//	// 监听窗口大小的调整
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// Init GLEW
//	glewExperimental = true;
//	if (glewInit() != GLEW_OK) {
//		cout << "Failed to init GLEW" << endl;
//		glfwTerminate();
//		return -1;
//	}
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
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//
//	// create and compile Shader
//	Shader* myShader = new Shader("vertexSource1.vert", "fragmentSource1.frag");
//
//	// position attribute
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	
//	// color attribute
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//	
//	glm::vec2 translations[100];
//	int index = 0;
//	float offset = 0.1f;
//	for (int y = -10; y < 10; y += 2)
//	{
//		for (int x = -10; x < 10; x += 2)
//		{
//			glm::vec2 translation;
//			translation.x = (float)x / 10.0f + offset;
//			translation.y = (float)y / 10.0f + offset;
//			translations[index++] = translation;
//		}
//	}
//
//	myShader->use();
//	for (unsigned int i = 0; i < 100; i++) {
//		stringstream ss;
//		string index;
//		ss << i;
//		index = ss.str();
//		unsigned int location = glGetUniformLocation(myShader->ID, ("offsets[" + index + "]").c_str());
//		glUniform2fv(location, 1, glm::value_ptr(translations[i]));
//	}
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		myShader->use();
//		glBindVertexArray(VAO);
//
//		// 之前都是使用glDrawArrays(GL_TRIANGLES, 0, 6)的方式绘制的，
//		// 但是如果像这样绘制模型的大量实例(Instance)，那么很快就会因为绘制调用过多而达到性能瓶颈。
//
//		// 使用glDrawArrays或glDrawElements函数告诉GPU去绘制你的顶点数据会消耗更多的性能，
//		// 因为OpenGL在绘制顶点数据之前需要做很多准备工作,比如：
//		// 告诉GPU该从哪个缓冲读取数据，从哪寻找顶点属性，而且这些都是在相对缓慢的CPU到GPU总线上进行的。
//		// 所以，即便渲染顶点非常快，命令GPU去渲染却未必。
//
//		// 如果能够将数据一次性发送给GPU，然后使用一个绘制函数让OpenGL利用这些数据绘制多个物体，就会更方便了。
//		// 这就是【实例化(Instancing)】
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
//
//		// 问题：
//		// 100是最大能够发送至着色器的uniform数据大小上限，所以当uniform数据过大时，就不能用【实例化】方式了；
//		// 【实例化】方式的替代方案就是【实例化数组】
//
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}
//
//// 窗口大小改变的回调
//void framebuffer_size_callback(GLFWwindow* window, int width, int height){
//	// 设置窗口维度
//	// 前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽度和高度(像素)
//	glViewport(0, 0, width, height);
//}
//
//// 按键处理
//void processInput(GLFWwindow* window) {
//	// 按下ESC键，关闭窗口
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// 加载纹理
//unsigned int loadTexture(char const * path) {
//	// 生成纹理对象
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	// 加载图片
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrChannels == 1)
//			format = GL_RED;
//		else if (nrChannels == 3)
//			format = GL_RGB;
//		else if (nrChannels == 4)
//			format = GL_RGBA;
//
//		// 绑定纹理
//		glBindTexture(GL_TEXTURE_2D, textureID); 
//		// 为当前绑定的纹理附加上纹理图像
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		// 为当前绑定的纹理自动生成所有需要的多级渐远纹理
//		glGenerateMipmap(GL_TEXTURE_2D);
//		// 为当前绑定的纹理设置环绕、过滤方式
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	else
//	{
//		cout << "Failed to load " << path << endl;
//	}
//	stbi_image_free(data);
//	return textureID;
//}