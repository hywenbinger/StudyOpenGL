//#include <iostream>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//
//using namespace std;
//
///*
//GLM��ר��ΪOpenGL����������ѧ��
//*/
//int main_glm() {
//
//	//��������
//	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//
//	//����4*4�ĵ�λ����
//	glm::mat4 trans;
//
//	//�����任����
//	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//	vec = trans * vec;
//
//	cout << vec.x << ", " << vec.y << ", " << vec.z << endl;
//
//	return 0;
//}