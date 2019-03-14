#include "Shader.h"
#include <iostream>
#include <fstream>//ifstream在此头文件下
using namespace std;//ifstream在此命名空间下
#include <sstream>//stringstream在此头文件下

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//::表示在Shader命名空间下
Shader::Shader(const char* vertexPaht,const char* fragmentPath)//这里参数要跟Shader.h中的构造函数的参数相同
{

	//ifstream 输入文件流
	ifstream vertexFile;
	ifstream fragmentFile;
	//声明stringstream
	stringstream vertexSStream;
	stringstream fragmentSStream;

	//打开文件
	vertexFile.open(vertexPaht);
	fragmentFile.open(fragmentPath);
	//打开失败和损坏的异常
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);
	//是否打开文件成功
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("Open File Error.");
		}
		//把文件导入到stringStream中
		vertexSStream << vertexFile.rdbuf();//<<导入符号，rdbuf 读取buff
		fragmentSStream << fragmentFile.rdbuf();

		//把stringSteam转成string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		
		//把string转成char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//声明顶点，片段
		unsigned int vertex, fragment;
		//创建vertexShader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		//绑定vertexShader源文件
		glShaderSource(vertex,1,&vertexSource,NULL);
		//编译
		glCompileShader(vertex);
		//检查
		checkCompileErrors(vertex,"VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment,1,&fragmentSource,NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment,"FRAGMENT");

		//创建程序
		ID = glCreateProgram();
		//把顶点shader粘到程序上
		glAttachShader(ID,vertex);
		//把片段shader粘到程序上
		glAttachShader(ID,fragment);
		//链接到程序
		glLinkProgram(ID);
		checkCompileErrors(ID,"PROGRAM");

		//清除掉顶点片段着色器
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

	//是否是程序
	if (type != "PROGRAM")
	{
		//那就是shader检测,参数：检测哪个番号，检测的类型，是否成功
		glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);
			cout << "Shader Compile Error:" << infoLog << endl;
		}
	}
	else
	{
		//是程序
		glGetProgramiv(ID,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(ID,512,NULL,infoLog);
			cout << "Program Link Error:" << infoLog << endl;
		}
	}
}
