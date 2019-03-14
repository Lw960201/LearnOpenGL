#include "Shader.h"
#include <iostream>
#include <fstream>//ifstream�ڴ�ͷ�ļ���
using namespace std;//ifstream�ڴ������ռ���
#include <sstream>//stringstream�ڴ�ͷ�ļ���

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//::��ʾ��Shader�����ռ���
Shader::Shader(const char* vertexPaht,const char* fragmentPath)//�������Ҫ��Shader.h�еĹ��캯���Ĳ�����ͬ
{

	//ifstream �����ļ���
	ifstream vertexFile;
	ifstream fragmentFile;
	//����stringstream
	stringstream vertexSStream;
	stringstream fragmentSStream;

	//���ļ�
	vertexFile.open(vertexPaht);
	fragmentFile.open(fragmentPath);
	//��ʧ�ܺ��𻵵��쳣
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	//�Ƿ���ļ��ɹ�
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("Open File Error.");
		}
		//���ļ����뵽stringStream��
		vertexSStream << vertexFile.rdbuf();//<<������ţ�rdbuf ��ȡbuff
		fragmentSStream << fragmentFile.rdbuf();

		//��stringSteamת��string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		
		//��stringת��char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//�������㣬Ƭ��
		unsigned int vertex, fragment;
		//����vertexShader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		//��vertexShaderԴ�ļ�
		glShaderSource(vertex,1,&vertexSource,NULL);
		//����
		glCompileShader(vertex);
		//���
		checkCompileErrors(vertex,"VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment,1,&fragmentSource,NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment,"FRAGMENT");

		//��������
		ID = glCreateProgram();
		//�Ѷ���shaderճ��������
		glAttachShader(ID,vertex);
		//��Ƭ��shaderճ��������
		glAttachShader(ID,fragment);
		//���ӵ�����
		glLinkProgram(ID);
		checkCompileErrors(ID,"PROGRAM");

		//���������Ƭ����ɫ��
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& e)
	{
		printf(e.what());
	}
}

void Shader::use(){
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type){
	int success;
	char infoLog[512];

	//�Ƿ��ǳ���
	if (type != "PROGRAM")
	{
		//�Ǿ���shader���,����������ĸ����ţ��������ͣ��Ƿ�ɹ�
		glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);
			cout << "Shader Compile Error:" << infoLog << endl;
		}
	}
	else
	{
		//�ǳ���
		glGetProgramiv(ID,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(ID,512,NULL,infoLog);
			cout << "Program Link Error:" << infoLog << endl;
		}
	}
}
