#pragma once
#include <string>


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
	void use();
	//~Shader();//析构函数
//private:
//	int a;
//	float b;
private:
	void checkCompileErrors(unsigned int ID,std::string type);
};

