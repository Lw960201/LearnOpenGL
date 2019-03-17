#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;
	Forward = glm::normalize(target - position);//Ŀ���ȥ�������λ���ٹ�һ���ɵ�λ����
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right,Forward));
}

Camera::Camera(glm::vec3 position, float pitch/*����*/, float yaw/*���ҽ�*/, glm::vec3 worldUp) {
	Position = position;
	WorldUp = worldUp;

	Pitch = pitch;
	Yaw = yaw;
	//��ͼ������ֵ����Ҫ��ͼ֪�����ͨ�������Ƕȼ������
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

//��������ƶ�
void  Camera::ProcessMouseMovement(float deltaX, float deltaY) {
	Pitch -= deltaY * SceneX;
	Yaw -= deltaX * SceneY;

	UpdateCameraVectors();
}

void Camera::UpdateCameraPos() {
	Position += Forward * SpeedZ * 0.1f;
}