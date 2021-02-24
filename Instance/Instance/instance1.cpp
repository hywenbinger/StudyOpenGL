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
//	// λ��          // ��ɫ
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//
//	-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//	 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//	 0.05f,  0.05f,  0.0f, 0.0f, 1.0f
//};
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
//	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "MyOpenGLWindow", NULL, NULL);
//	if (window == NULL) {
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// �������ڴ�С�ĵ���
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
//		// ֮ǰ����ʹ��glDrawArrays(GL_TRIANGLES, 0, 6)�ķ�ʽ���Ƶģ�
//		// �����������������ģ�͵Ĵ���ʵ��(Instance)����ô�ܿ�ͻ���Ϊ���Ƶ��ù�����ﵽ����ƿ����
//
//		// ʹ��glDrawArrays��glDrawElements��������GPUȥ������Ķ������ݻ����ĸ�������ܣ�
//		// ��ΪOpenGL�ڻ��ƶ�������֮ǰ��Ҫ���ܶ�׼������,���磺
//		// ����GPU�ô��ĸ������ȡ���ݣ�����Ѱ�Ҷ������ԣ�������Щ��������Ի�����CPU��GPU�����Ͻ��еġ�
//		// ���ԣ�������Ⱦ����ǳ��죬����GPUȥ��Ⱦȴδ�ء�
//
//		// ����ܹ�������һ���Է��͸�GPU��Ȼ��ʹ��һ�����ƺ�����OpenGL������Щ���ݻ��ƶ�����壬�ͻ�������ˡ�
//		// ����ǡ�ʵ����(Instancing)��
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
//
//		// ���⣺
//		// 100������ܹ���������ɫ����uniform���ݴ�С���ޣ����Ե�uniform���ݹ���ʱ���Ͳ����á�ʵ��������ʽ�ˣ�
//		// ��ʵ��������ʽ������������ǡ�ʵ�������顿
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
//// ���ڴ�С�ı�Ļص�
//void framebuffer_size_callback(GLFWwindow* window, int width, int height){
//	// ���ô���ά��
//	// ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�Ⱥ͸߶�(����)
//	glViewport(0, 0, width, height);
//}
//
//// ��������
//void processInput(GLFWwindow* window) {
//	// ����ESC�����رմ���
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//// ��������
//unsigned int loadTexture(char const * path) {
//	// �����������
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	// ����ͼƬ
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
//		// ������
//		glBindTexture(GL_TEXTURE_2D, textureID); 
//		// Ϊ��ǰ�󶨵�������������ͼ��
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		// Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
//		glGenerateMipmap(GL_TEXTURE_2D);
//		// Ϊ��ǰ�󶨵��������û��ơ����˷�ʽ
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