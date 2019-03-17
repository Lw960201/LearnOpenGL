#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;
	Forward = glm::normalize(target - position);//目标减去摄像机的位置再归一化成单位向量
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right,Forward));
}

Camera::Camera(glm::vec3 position, float pitch/*俯角*/, float yaw/*左右角*/, glm::vec3 worldUp) {
	Position = position;
	WorldUp = worldUp;
	//画图出来的值（需要画图知道如何通过两个角度计算出）
	Forward.x = glm::cos(pitch) *glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch)*glm::cos(yaw);

	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position,Forward + Position,WorldUp);
}