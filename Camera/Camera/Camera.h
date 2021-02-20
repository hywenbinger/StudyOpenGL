#pragma once //防止一个头文件被编译多次，等价于下面的 ifndef/define/endif

//#ifndef CAMERA_H
//#define CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	/*
	position: camera位置
	target: 目标位置
	worldup: 上向量
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

