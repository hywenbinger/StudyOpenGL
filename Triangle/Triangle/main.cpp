#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int width = 800;
int height = 600;

// ����ESC�����رմ���
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// ��������
float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
};

// �������ݣ�ע��������0��ʼ
// ע�⣺��ʱ����Ƶ������棬˳ʱ����Ƶ��ڱ���
unsigned int indices[] = { 
	0, 3, 1, // ��һ��������
	1, 3, 2  // �ڶ���������
};

// ������ɫ��
const char* vertexShaderSource =
"#version 330 core  \n"
"layout(location = 6) in vec3 aPos;  \n"
"void main(){  \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}  \n";

// Ƭ����ɫ��
const char* fragmentShaderSource =
"#version 330 core  \n"
"out vec4 FragColor;  \n"
"void main() {  \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}  \n";

// ������
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

	// ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�������ֵ��
	glViewport(0, 0, width, height);

	// �����޳�����(Ĭ�����涼�ǻ��Ƶ�)
	glEnable(GL_CULL_FACE); 
	// �޳�����
	glCullFace(GL_BACK);

	// �߿�ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	---------------------�ص�----------��ʼ---------------------
	*/

	// ����һ����VAO������
	unsigned int VAO; // �ȼ��ڣ�unsigned int VAO[1];
	glGenVertexArrays(1, &VAO); // �ȼ��ڣ�glGenVertexArrays(1, VAO);
	// ��VAO
	glBindVertexArray(VAO);

	// ����һ����VBO������
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// VBO�󶨵�ARRAY_BUFFER��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �Ѷ������ݸ��Ƶ�VBO��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����һ����EBO������
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	// EBO�󶨵�ELEMENT_ARRAY_BUFFER��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// ���������ݸ��Ƶ�EBO�� 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���ˣ��Ѿ��Ѷ������ݺ��������ݴ������Կ����ڴ��У��ֱ���VBO��EBO����
	// ����ᴴ��һ�������Ƭ����ɫ��������������Щ����

	// ���ɡ�������ɫ��������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �ѡ�������ɫ��Դ�롿���ӵ�������ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// ���붥����ɫ��
	glCompileShader(vertexShader);

	// ���ɡ�Ƭ����ɫ��������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// �ѡ�Ƭ����ɫ��Դ�롿���ӵ�Ƭ����ɫ��������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// ����Ƭ����ɫ��
	glCompileShader(fragmentShader);

	// ���ˣ�������ɫ�����������
	// ������������ɫ���������ӵ�һ��������Ⱦ����ɫ������(Shader Program)��

	// ��������ɫ�����򡿶���
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// ��֮ǰ�������ɫ�����ӵ����������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ������ɫ���������
	glLinkProgram(shaderProgram);
	// ������ɫ���������
	glUseProgram(shaderProgram);

	// ����ɫ���������ӵ���ɫ����������Ժ󣬼ǵ�ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ���ˣ��Ѿ������붥�����ݷ��͸���GPU����ָʾ��GPU����ڶ����Ƭ����ɫ���д�����
	// ��ĿǰOpenGL����֪������ν����ڴ��еĶ������ݣ��Լ�����ν������������ӵ�������ɫ����������
	// ���ԣ���������Ⱦǰָ��OpenGL����ν��Ͷ�������

	// ����OpenGL����ν����������ݣ������ö�������ָ��
	// ��һ��������Ӧ vertexShaderSource �е� layout
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ����������6�ġ��������ԡ�����������Ĭ���ǽ��õ�
	glEnableVertexAttribArray(6);

	/*
	---------------------�ص�----------����---------------------
	*/

	// ����һ����Ⱦѭ����Render Loop��
	while (!glfwWindowShouldClose(window)) {
		// ��������
		processInput(window);

		// ��Ⱦ
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); // �����Ļ��ɫ����

		/*
		---------------------����������----------��ʼ---------------------
		*/
		glUseProgram(shaderProgram); 
		glBindVertexArray(VAO); 
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		/*
		---------------------����������----------����---------------------
		*/

		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// �ͷ���Դ
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}