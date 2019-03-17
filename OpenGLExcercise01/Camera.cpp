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

	Pitch = pitch;
	Yaw = yaw;
	//画图出来的值（需要画图知道如何通过两个角度计算出）
	Forward.x = glm::cos(Pitch) *glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);

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

void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) *glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch)*glm::cos(Yaw);

	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

//处理鼠标移动
void  Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SceneX;
	Yaw -= deltaX * SceneY;

	UpdateCameraVectors();
}

void Camera::UpdateCameraPos() {
	Position += Forward * SpeedZ * 0.1f;
}