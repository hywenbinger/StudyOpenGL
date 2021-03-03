#define GLEW_STATIC

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

int screenWidth = 800;
int screenHeight = 600;

// time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
unsigned int loadCubemap(vector<std::string> faces);

// 顶点数据
float vertices[] = {
	1.0f, 1.0f,   1.0f, 1.0f,   
	1.0f, 0.5f,   1.0f, 0.0f,  
	0.5f, 0.5f,   0.0f, 0.0f,  
	0.5f, 1.0f,   0.0f, 1.0f    
};
unsigned int indices[] = {
	0, 2, 1,
	0, 3, 2
};

// 顶点坐标
float skyboxVertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

// 图片路径
vector<std::string> faces
{
	"right.jpg",
	"left.jpg",
	"top.jpg",
	"bottom.jpg",
	"front.jpg",
	"back.jpg"
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
	// 监听窗口大小的调整
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cout << "Failed to init GLEW" << endl;
		glfwTerminate();
		return -1;
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	// plane
	unsigned int planeVAO;
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);
	unsigned int planeVBO;
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int planeEBO;
	glGenBuffers(1, &planeEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// plane shader
	Shader* planeShader = new Shader("planeVS.vert", "planeFS.frag");
	planeShader->use();
	// plane vertex
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// plane texture
	int planeTextureIndex = 2;
	unsigned int planeTexture = loadTexture("left.jpg");
	glUniform1i(glGetUniformLocation(planeShader->ID, "plane"), planeTextureIndex);

	// skybox
	unsigned int skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);
	unsigned int skyboxVBO;
	glGenBuffers(1, &skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	// skybox shader
	Shader* skyboxShader = new Shader("skyboxVS.vert", "skyboxFS.frag");
	skyboxShader->use();
	// skybox vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// skybox texture
	int skyboxTextureIndex = 7;
	unsigned int skyboxTexture = loadCubemap(faces);
	glUniform1i(glGetUniformLocation(skyboxShader->ID, "skybox"), skyboxTextureIndex);
	// skybox projection matrix
	glm::mat4 projectionMat;
	projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "projectionMat"),
		1, GL_FALSE, glm::value_ptr(projectionMat));
	// skybox model matrix
	glm::mat4 modelMat;
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -5.0f));
	modelMat = glm::rotate(modelMat, glm::radians(30.0f), glm::vec3(1.0f, 0.2f, 0.5f));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "modelMat"),
		1, GL_FALSE, glm::value_ptr(modelMat));

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// plane
		planeShader->use();
		glActiveTexture(GL_TEXTURE0 + planeTextureIndex);
		glBindTexture(GL_TEXTURE_2D, planeTexture);
		glBindVertexArray(planeVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glDepthMask(GL_FALSE);
		//glDepthFunc(GL_LEQUAL);

		// skybox
		skyboxShader->use();
		// skybox view matrix
		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "viewMat"),
			1, GL_FALSE, glm::value_ptr(viewMat));
		// draw skybox
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0 + skyboxTextureIndex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glDepthMask(GL_TRUE);
		//glDepthFunc(GL_LESS);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &planeVAO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteBuffers(1, &planeEBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

	glfwTerminate();
	return 0;
}

// 窗口大小改变的回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	// 设置窗口维度
	// 前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽度和高度(像素)
	glViewport(0, 0, width, height);
}

// 按键处理
void processInput(GLFWwindow* window) {
	// 按下ESC键，关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	// 控制Camera移动
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		cout << "Failed to load " << path << endl;
	}
	stbi_image_free(data);
	return textureID;
}

unsigned int loadCubemap(vector<std::string> faces){
	// 生成纹理对象
	unsigned int textureID;
	glGenTextures(1, &textureID);
	// 绑定纹理
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	// 加载图片
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			// 为当前绑定的纹理附加上纹理图像
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
		}
		stbi_image_free(data);
	}
	// 为当前绑定的纹理设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return textureID;
}