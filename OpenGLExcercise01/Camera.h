#pragma once//��ֹһ����ͷ���������Σ���������������ֹ��������

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position,glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position,float pitch,float yaw, glm::vec3 worldUp);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	glm::mat4 GetViewMatrix();
};


