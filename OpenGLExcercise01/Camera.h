#pragma once//防止一个标头被编译两次，所以用这句代码阻止编译两次

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
	//俯角，左右角
	float Pitch;
	float Yaw;
	//旋转角度缩放
	float SceneX = 0.001f;
	float SceneY = 0.001f;
	//摄像机移动Z方向的移动速度
	float SpeedZ = 0;

	//得到View矩阵
	glm::mat4 GetViewMatrix();
	//处理鼠标移动
	void ProcessMouseMovement(float deltaX,float deltaY);
	//按WS控制摄像机前后移动
	void UpdateCameraPos();
private:
	//更新摄像机向量
	void UpdateCameraVectors();
};


