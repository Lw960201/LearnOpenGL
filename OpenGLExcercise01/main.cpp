//ͷ�ļ�����========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//ϵͳ�Դ���ͷ�ļ���<>����Ŀ�µ�ͷ�ļ���""
//====��ͼƬ������api============
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//ģ�Ͷ�������=======================================================================
//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//
//};

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);

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


	//================���ö�������ֵ���綥��λ�ã�������ɫ����������==============================================
	//��������ֵ������1�������￪ʼ������2��һ�������٣�����3������ʲô���͵Ķ��㣬
	//����4���Ƿ����滯����1֮�䣬����5��ÿ�λ�ȡ���������٣�����6����һ�λ�ȡ��ƫ�ƶ��ٵĵط���ʼ
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)0);
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//������������ֵ���õ�shader��
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//������������ֵ���õ�shader��
	glEnableVertexAttribArray(2);

	//====================TEXTURE_2D_BUFFER============================================
    //����һ��texBuffer
	unsigned int texBufferA;
	glGenTextures(1, &texBufferA);
	//�󶨣���֮�����������������õ�ǰ�󶨵�����
	glBindTexture(GL_TEXTURE_2D, texBufferA);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//����ԭͼ============================================================================
	int width, height, nrChannels;//ͼ��ͼ�ߣ���ɫͨ��
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	//���������
	if (data)
	{
		//��ȾͼƬ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0/*�Ƿ�Ҫ��Ե*/, GL_RGB, GL_UNSIGNED_BYTE, data);
		//����GL_TEXTURE_2D�ϵ�ͼ����������mipmap������Ҫ
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//�����ڴ���ͷ��ڴ�
	stbi_image_free(data);

	//����һ��texBuffer
	unsigned int texBufferB;
	glGenTextures(1, &texBufferB);
	glActiveTexture(GL_TEXTURE1);
	//�󶨣���֮�����������������õ�ǰ�󶨵�����
	glBindTexture(GL_TEXTURE_2D, texBufferB);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//����ԭͼ============================================================================
	//int width, height, nrChannels;//ͼ��ͼ�ߣ���ɫͨ��
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	//���������
	if (data)
	{
		//��ȾͼƬ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0/*�Ƿ�Ҫ��Ե*/, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//����GL_TEXTURE_2D�ϵ�ͼ����������mipmap������Ҫ
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//�����ڴ���ͷ��ڴ�
	stbi_image_free(data);

	myShader->use();
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);
	//===================�����任==========================================
	//glm::mat4 trans;
	//λ�ơ�������Ҫ��ֵ��Ŀ�꣬Ҫ�ƶ���ֵ
	//trans = glm::translate(trans,glm::vec3(-1.0f,0,0));
	//��ת���ȡ�������Ҫ��ֵ��Ŀ�꣬���ȣ�glm::radians�������԰ѽǶ�ת���ȣ�����ת��
	//trans = glm::rotate(trans,glm::radians(45.0f),glm::vec3(0,0,1.0f));
	//���š�������Ҫ���ݵ�ֵ������ֵ
	//trans = glm::scale(trans,glm::vec3(2.0f, 2.0f, 2.0f));
	//====================�ռ�任========================================
	glm::mat4 modelMat;
	modelMat = glm::rotate(modelMat,glm::radians(-55.0f),glm::vec3(1.0f,0,0));
	glm::mat4 viewMat;
	viewMat = glm::translate(viewMat,glm::vec3(0,0,-3.0f));
	glm::mat4 projMat;
	//ͶӰ�任���������ӽǴ�С�����ݱȣ����ü��棬Զ�ü���(������γ����Ͳü�)
	projMat = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);

	//===================��Ⱦѭ��==================================================
	//�������û�йر�
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 trans;
		//�����ƶ�����
		//trans = glm::translate(trans, glm::vec3(-0.01f, 0, 0));
		//��ת
		trans = glm::rotate(trans, (float)(glfwGetTime())/* glm::radians(45.0f)*/, glm::vec3(0, 0, 1.0f));
		//����
		//trans = glm::scale(trans, glm::vec3( (float)sin(2*glfwGetTime()),(float)sin(2*glfwGetTime()), (float)sin(2*glfwGetTime()) ));
		//���ڴ˴��ڰ���ESC
		processInput(window);
		//��մ�����ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//�����ɫ���������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
		//���������
		glActiveTexture(GL_TEXTURE0);
		//������A
		glBindTexture(GL_TEXTURE_2D, texBufferA);
		//���������
		glActiveTexture(GL_TEXTURE1);
		//������B
		glBindTexture(GL_TEXTURE_2D, texBufferB);

		myShader->use();
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		//uniform������λ��
		unsigned int transformLoc = glGetUniformLocation(myShader->ID, "transform");
		unsigned int modelMatLoc = glGetUniformLocation(myShader->ID, "modelMat");
		unsigned int viewMatLoc = glGetUniformLocation(myShader->ID, "viewMat");
		unsigned int projMatLoc = glGetUniformLocation(myShader->ID, "projMat");
		//���ľ����ֵ�����������ĵı���λ�ã������������Ƿ�Ծ���ת�ã������ľ������ݣ���Ҫͨ��glm::value_ptr(trans)����ת��Ϊopengl�ܽ��ܵ�ֵ��
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));

		//����������,����1��Ҫ�������ͣ�����2������������ʼ������3������������
		glDrawArrays(GL_TRIANGLES,0,36);
		//ͨ���������������������������ͣ��ߴ磬����ʲô���ͣ�ƫ��ֵ
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		//ת��ǰ��Buffer
		glfwSwapBuffers(window);
		//��ȡ�¼�
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//����ڴ�
	glfwTerminate();

	return 0;
}

