#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>//跟opengl做互传的时候需要

class Shader
{
public://在C++中相同修饰符的变量要放一起
	Shader(const char* vertexPaht, const char* fragmentPath);//构造函数
	//声明string
	std::string vertexString;
	std::string fragmentString;
	//声明char*
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
	//~Shader();//析构函数
//private:
//	int a;
//	float b;
private:
	void checkCompileErrors(unsigned int ID,std::string type);
};

