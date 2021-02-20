#pragma once //��ֹһ��ͷ�ļ��������Σ��ȼ�������� ifndef/define/endif

//#ifndef CAMERA_H
//#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	/*
	position: cameraλ��
	target: Ŀ��λ��
	worldup: ������
	*/
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	glm::vec3 Position;
	glm::vec3 WorldUp;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::mat4 GetViewMatrix();
};

//#endif 

