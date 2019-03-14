//ͷ�ļ�����========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//ϵͳ�Դ���ͷ�ļ���<>����Ŀ�µ�ͷ�ļ���""

//ģ�Ͷ�������=======================================================================
float vertices[] = {
	 -1, -1, 0.0f,1,0,0,		//0
	 -0.5f, 0.5f, 0.0f,0,1,0,	//1
	 0.5f,  -0.5f, 0.0f,0,0,1,//2
	 //-0.5f, 0.5f, 0.0f,
	 //0.5f,  -0.5f, 0.0f,
     1, 1, 0.0f,0.2f,0.3f,0.7f			//3

	////���½�
	//-1,-1,0, 1,0,0,//0
	//0,-1,0,0, 1,0,//1
	//-1,0,0, 0,0,1,//2
	////���½�
	//0,-1,0,0,0,1,
	//1,-1,0, 1,0,0,//3
	//1,0,0, 0,1,0,//4
	////���Ͻ�
	//1,0,0, 0,0,1,//5
	//1,1,0, 1,0,0,//6
	//0,1,0, 0,1,0,//7
	////���Ͻ�
	//0,1,0,0,0,1,
	//-1,1,0, 1,0,0,//8
	//-1,0,0,0,1,0

};
//��������ʾһ�������棺0��1��2    2��1��3.���Լ�����ͬ���������

unsigned int indices[] = {//ע��������0��ʼ
	0,1,2,//��һ��������
	1,2,3 //�ڶ���������
	//0,1,2,
	//1,3,4,
	//5,6,7,
	//7,8,2
};

//����ESC�رմ���====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}
}

//======================������ɫ��GLSL==============================================
//const char* vertexShaderSource =
//"#version 330 core										 \n"
//"layout (location = 0) in vec3 aPos;                     \n"
//"layout (location = 1) in vec3 aColor;                     \n"
//"out vec4 vertexColor;                                   \n"
//"void main(){                                            \n"
//"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);    \n"
//"    vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0);                    \n"
//"}   \n";
//=======================Ƭ����ɫ��GLSL=============================================
//const char* fragmentShaderSource =
//"#version 330 core								 \n"
//"out vec4 FragColor;							 \n"
//"in  vec4 vertexColor;							 \n"
//"uniform vec4 ourColor;							 \n"
//"void main(){                                    \n"
//"    FragColor = vertexColor;                 }  \n";

int main2()
{
	//===================��ʼ��====================================================
	//��ʼ��glfw��
	glfwInit();
	//��汾��3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//С�汾��3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	//�ɱ�̹���
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	//======================����===================================================
	//���� GLFW ����
	GLFWwindow* window = glfwCreateWindow(800,600,"My OpenGL Game",NULL,NULL);

	//����ǿ��򿪴�ʧ��
	if (window == NULL)
	{
		printf("Open Window Faild!");
		//��������
		glfwTerminate();
		return -1;
	}

	//window����ʹ���������ģ�����ʹ��window��
	glfwMakeContextCurrent(window);

	//��ʼ�� GLEW
	glewExperimental = true;
	//�����ʼ��GLEWʧ��
	if (glewInit()!=GLEW_OK)
	{
		printf("Init GLEW Faild!");
		glfwTerminate();
		return -1;
	}

	glViewport(0,0,800,600);
	//����ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//====================�����޳�===========================================
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//opengl�涨��ʱ����������ε�����
	//=====================VAO===============================================

	//Shader testShader = Shader("vertexSource.txt","fragmentSource.txt");
	//testShader.test();//�������.ʹ��
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	//testShader->test();//ָ�����->ʹ��

	unsigned int VAO;//Vertex Array Object
	//����һ��VAO
	glGenVertexArrays(1,&VAO);
	//��
	glBindVertexArray(VAO);
	//=====================VBO===============================================
	unsigned int VBO;//Vertex Buffer Object
	//����һ��VBO
	glGenBuffers(1,&VBO);
	//��ARRAY_BUFFER����VAO��
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//��������ͨ��ARRAY_BUFFER����VAO.����1�����ݵ�Ŀ�꣬����2:���ݵĳߴ磬����3�����ݣ�����4�����Ƶ������Ƿ񳣱�
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//=====================EBO================================================
	unsigned int EBO;//�����������
	//����һ��EBO
	glGenBuffers(1,&EBO);
	//��EBO��GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	//��GL_ELEMENT_ARRAY_BUFFER�д�������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	////===================������ɫ��============================================
	////������ɫ������
	//unsigned int vertexShader;
	////����һ��VertexShader
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////��Դ�ļ���ֵ��VertexShader
	//glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	////����VertexShader
	//glCompileShader(vertexShader);
	////====================Ƭ����ɫ��===========================================
	////Ƭ����ɫ������
	//unsigned int fragmentShader;
	////����һ��fragmentShader
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	////��Դ�ļ���ֵ��fragmentShader
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	////����fragmentShader
	//glCompileShader(fragmentShader);
	////====================��ɫ����=============================================
	////��shader����shaderProgram
	//unsigned int shaderProgram;
	////����һ��shaderProgrma
	//shaderProgram = glCreateProgram();
	////��VertexShader��FragmentShader����ShaderProgram
	//glAttachShader(shaderProgram,vertexShader);
	//glAttachShader(shaderProgram,fragmentShader);
	////���ӵ�ShaderProgram
	//glLinkProgram(shaderProgram);

	//��������ֵ������1�������￪ʼ������2��һ�������٣�����3������ʲô���͵Ķ��㣬
	//����4���Ƿ����滯����1֮�䣬����5��ÿ�λ�ȡ���������٣�����6����һ�λ�ȡ��ƫ�ƶ��ٵĵط���ʼ
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(1);

	//===================��Ⱦѭ��==================================================
	//�������û�йر�
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		////��ȡʱ��
		//float timeValue = glfwGetTime();
		////��timeColor��ֵӳ�䵽0��1֮��
		//float changeTimeValue = (sin(5*timeValue) / 2.0f) + 0.5f;
		////��ȡshaderProgram�е�ourColor
		//int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
		////ʹ�ó���
		//glUseProgram(shaderProgram);
		////��ourColor��ֵ
		//glUniform4f(vertexColorLocation, (sin(5 * timeValue) / 2.0f) + 0.5f, (sin(5 * timeValue + 0.5f) / 2.0f) + 0.5f, (sin(5 * timeValue + 1.0f) / 2.0f) + 0.5f, 1.0f);
	
		myShader->use();

		//����������,����1��Ҫ�������ͣ�����2������������ʼ������3������������
		//glDrawArrays(GL_TRIANGLES,0,12);
		//ͨ���������������������������ͣ��ߴ磬����ʲô���ͣ�ƫ��ֵ
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		//ת��ǰ��Buffer
		glfwSwapBuffers(window);
		//��ȡ�¼�
		glfwPollEvents();
	}

	//����ڴ�
	glfwTerminate();

	return 0;
}

