#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
	//����
	glm::vec4 vec(1.0f,0,0,1.0f);

	glm::mat4 trans;//Ĭ���ǵ�λ����
	trans = glm::translate(trans,glm::vec3(2.0f,0,0));//�þ����ʾλ�ƾ���
	//����任
	vec = trans * vec;

	std::cout << vec.x << vec.y << vec.z << std::endl;

	while (true)
	{

	}

	return 0;
}