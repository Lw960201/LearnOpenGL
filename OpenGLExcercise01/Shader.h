#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>//��opengl��������ʱ����Ҫ

class Shader
{
public://��C++����ͬ���η��ı���Ҫ��һ��
	Shader(const char* vertexPaht, const char* fragmentPath);//���캯��
	//����string
	std::string vertexString;
	std::string fragmentString;
	//����char*
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;//Shader Program ID

	enum Slot
	{
		DIFFUSE,
		SPECULAR,
		EMISSION
	};

	void use();
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char* paramNameString, float param);
	void SetUniform1i(const char* paramNameString,int param);
	//~Shader();//��������
//private:
//	int a;
//	float b;
private:
	void checkCompileErrors(unsigned int ID,std::string type);
};

