//#define GLEW_STATIC
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//using namespace std;
//
//int screenWidth = 800;
//int screenHeight = 600;
//
//// time
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;
//
//// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//bool firstMouse = true;
//float yaw = -90.0f;	
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//float fov = 45.0f;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//
//// 顶点数据
//float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
//// 为每个立方体定义一个位移向量来指定它在世界空间的位置
//glm::vec3 cubePositions[] = {
//  glm::vec3(0.0f,  0.0f,  0.0f),
//  glm::vec3(2.0f,  5.0f, -15.0f),
//  glm::vec3(-1.5f, -2.2f, -2.5f),
//  glm::vec3(-3.8f, -2.0f, -12.3f),
//  glm::vec3(2.4f, -0.4f, -3.5f),
//  glm::vec3(-1.7f,  3.0f, -7.5f),
//  glm::vec3(1.3f, -2.0f, -2.5f),
//  glm::vec3(1.5f,  2.0f, -2.5f),
//  glm::vec3(1.5f,  0.2f, -1.5f),
//  glm::vec3(-1.3f,  1.0f, -1.5f)
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
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	// 监听鼠标移动
//	glfwSetCursorPosCallback(window, mouse_callback);
//	// 监听鼠标滚轮
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// Init GLEW
//	glewExperimental = true;
//	if (glewInit() != GLEW_OK) {
//		cout << "Failed to init GLEW" << endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//	glEnable(GL_DEPTH_TEST);
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
//	// create and compile Shader
//	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// uv attribute
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// 第一个纹理
//	int textureIndex1 = 2;
//	unsigned int textureID1 = loadTexture("container.jpg");
//
//	// 第二个纹理
//	int textureIndex2 = 7;
//	unsigned int textureID2 = loadTexture("awesomeface.png");
//
//	// 设置uniform变量之前一定要激活着色器程序!
//	myShader->use();
//
//	// 设置着色器中的sample属于哪个纹理单元
//	glUniform1i(glGetUniformLocation(myShader->ID, "texture1"), textureIndex1);
//	glUniform1i(glGetUniformLocation(myShader->ID, "texture2"), textureIndex2);
//
//	while (!glfwWindowShouldClose(window)) {
//
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glActiveTexture(GL_TEXTURE0 + textureIndex1);
//		glBindTexture(GL_TEXTURE_2D, textureID1);
//		glActiveTexture(GL_TEXTURE0 + textureIndex2);
//		glBindTexture(GL_TEXTURE_2D, textureID2);
//
//		myShader->use();
//
//		// 观察矩阵
//		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"),
//			1, GL_FALSE, glm::value_ptr(viewMat));
//
//
//		// 透视矩阵
//		glm::mat4 projectionMat;
//		projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projectionMat"),
//			1, GL_FALSE, glm::value_ptr(projectionMat));
//
//		glBindVertexArray(VAO);
//
//		// 画十个立方体
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			// 模型矩阵
//			glm::mat4 modelMat;
//			modelMat = glm::translate(modelMat, cubePositions[i]);
//			float angle = 20.0f * (i + 1);
//			modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(1.0f, 0.2f, 0.5f));
//			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"),
//				1, GL_FALSE, glm::value_ptr(modelMat));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
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
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//void framebuffer_size_callback(GLFWwindow* window, int width, int height){
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//void mouse_callback(GLFWwindow* window, double xpos, double ypos){
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.1f; // change this value to your liking
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// make sure that when pitch is out of bounds, screen doesn't get flipped
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	cameraFront = glm::normalize(front);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
//	fov -= (float)yoffset;
//	if (fov < 1.0f)
//		fov = 1.0f;
//	if (fov > 45.0f)
//		fov = 45.0f;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//void processInput(GLFWwindow* window) {
//	// 按下ESC键，关闭窗口
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	// 控制Camera移动
//	float cameraSpeed = 2.5 * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		cameraPos += cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//	else
//	{
//		cout << "Failed to load " << path << endl;
//	}
//	stbi_image_free(data);
//	return textureID;
//}