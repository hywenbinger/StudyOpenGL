//#include <iostream>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//using namespace std;
//
///*
//GLM：专门为OpenGL量身定做的数学库
//*/
//int main_glm() {
//
//	//定义向量
//	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//
//	//定义4*4的单位矩阵
//	glm::mat4 trans;
//
//	//创建变换矩阵
//	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//	vec = trans * vec;
//
//	cout << vec.x << ", " << vec.y << ", " << vec.z << endl;
//
//	return 0;
//}