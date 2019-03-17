#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
	//顶点
	glm::vec4 vec(1.0f,0,0,1.0f);

	glm::mat4 trans;//默认是单位矩阵
	trans = glm::translate(trans,glm::vec3(2.0f,0,0));//用矩阵表示位移矩阵
	//矩阵变换
	vec = trans * vec;

	std::cout << vec.x << vec.y << vec.z << std::endl;

	while (true)
	{

	}

	return 0;
}