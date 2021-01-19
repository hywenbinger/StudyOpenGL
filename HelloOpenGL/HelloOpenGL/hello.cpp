#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;

// ����ESC�����رմ���
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

	// ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�������ֵ��
	glViewport(0, 0, width, height);

	// ����һ����Ⱦѭ����Render Loop��
	while (!glfwWindowShouldClose(window)){
		// ��������
		processInput(window);

		// ��Ⱦ
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); // �����Ļ��ɫ����

		// glClearColor������һ��״̬���ú�����
		// glClear��������һ��״̬ʹ�õĺ�������ʹ���˵�ǰ��״̬����ȡӦ�����Ϊʲô��ɫ

		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// �ͷ���Դ
	glfwTerminate();

	return 0;
}