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
	//��ͼ������ֵ����Ҫ��ͼ֪�����ͨ�������Ƕȼ������
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