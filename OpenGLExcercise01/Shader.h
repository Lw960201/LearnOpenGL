#pragma once
#include <string>


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
	void use();
	//~Shader();//��������
//private:
//	int a;
//	float b;
private:
	void checkCompileErrors(unsigned int ID,std::string type);
};

