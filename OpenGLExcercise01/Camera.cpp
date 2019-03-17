#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;
	Forward = glm::normalize(target - position);//目标减去摄像机的位置再归一化成单位向量
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right,Forward));
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position,Forward + Position,WorldUp);
}