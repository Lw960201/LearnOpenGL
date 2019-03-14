//ͷ�ļ�����========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//ϵͳ�Դ���ͷ�ļ���<>����Ŀ�µ�ͷ�ļ���""
//====��ͼƬ������api============
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//ģ�Ͷ�������=======================================================================
float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����

};
//��������ʾһ�������棺0��1��2    2��1��3.���Լ�����ͬ���������

unsigned int indices[] = {//ע��������0��ʼ
	0,1,3,//��һ��������
	2,3,1 //�ڶ���������
};

//����ESC�رմ���====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}
}


int main()
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
	//====================TEXTURE_2D_BUFFER============================================
	//����һ��texBuffer
	unsigned int texBuffer;
	glGenTextures(1,&texBuffer);
	//�󶨣���֮�����������������õ�ǰ�󶨵�����
	glBindTexture(GL_TEXTURE_2D,texBuffer);

	//����ԭͼ
	int width, height, nrChannels;//ͼ��ͼ�ߣ���ɫͨ��
	unsigned char *data = stbi_load("container.jpg",&width,&height,&nrChannels,0);
	if (data)
	{
		//
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0/*�Ƿ�Ҫ��Ե*/,GL_RGB,GL_UNSIGNED_BYTE,data);
		//����GL_TEXTURE_2D�ϵ�ͼ����������mipmap������Ҫ
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//�����ڴ���ͷ��ڴ�
	stbi_image_free(data);
	//================���ö�������ֵ���綥��λ�ã�������ɫ����������==============================================
	//��������ֵ������1�������￪ʼ������2��һ�������٣�����3������ʲô���͵Ķ��㣬
	//����4���Ƿ����滯����1֮�䣬����5��ÿ�λ�ȡ���������٣�����6����һ�λ�ȡ��ƫ�ƶ��ٵĵط���ʼ
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(2);

	//===================��Ⱦѭ��==================================================
	//�������û�йر�
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D,texBuffer);
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	
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

