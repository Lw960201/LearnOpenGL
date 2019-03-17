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
#include <glm/gtc/type_ptr.hpp>//��opengl��������ʱ����Ҫ

#include "Camera.h"

#pragma region Model Data
//һ��Cube�Ķ�������
float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

//���cube��λ��
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Camera Declare
//ʵ���������
//Camera camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Input Declare(����)
//ǰһ�ε��������
float lastX;
float lastY;
bool firstMouse = true;

//����ESC�رմ���====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.SpeedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.SpeedZ = -1.0f;
	}
	else
	{
		camera.SpeedZ = 0;
	}
}

//���ص��������������GLFWwindow*��double��double
void mouse_callback(GLFWwindow* window,double xPos,double yPos) {
	//�����״�ƫ��ֵ̫��
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	//ÿ�ε�ƫ����
	float deltaX, deltaY;
	//����һ�����λ�õ�ƫ����
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	//����һ�ε��������ֵ��ֵ����һ�ε��������ֵ
	lastX = xPos;
	lastY = yPos;
	//printf("%f \n",deltaX);

	camera.ProcessMouseMovement(deltaX,deltaY);
}

#pragma endregion

unsigned int LoadImageToGPU(const char* fileName,GLint internalFormat,GLenum format,int textrueSlot)
{
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0 + textrueSlot);
	//�󶨣���֮�����������������õ�ǰ�󶨵�����
	glBindTexture(GL_TEXTURE_2D, texBuffer);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;//ͼ��ͼ�ߣ���ɫͨ��
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	//���������
	if (data)
	{
		//��ȾͼƬ
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0/*�Ƿ�Ҫ��Ե*/, format, GL_UNSIGNED_BYTE, data);
		//����GL_TEXTURE_2D�ϵ�ͼ����������mipmap������Ҫ
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//�����ڴ���ͷ��ڴ�
	stbi_image_free(data);

	return texBuffer;
}

int main()
{
	#pragma region Open a Window

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

		//�ص������ʾ.�������ĸ����ڣ�������ͣ��������
		glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
		//������ƶ�ʱ���ûص��ص��������������ĸ����ڱ���⣬�����ĸ�����
		glfwSetCursorPosCallback(window,mouse_callback);

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
	#pragma endregion

	#pragma region Init Shader Program
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

	#pragma region Init and Load Models to VAO,VBO

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

		//================���ö�������ֵ���綥��λ�ã�������ɫ����������==============================================
		//��������ֵ������1�������￪ʼ������2��һ�������٣�����3������ʲô���͵Ķ��㣬
		//����4���Ƿ����滯����1֮�䣬����5��ÿ�λ�ȡ���������٣�����6����һ�λ�ȡ��ƫ�ƶ��ٵĵط���ʼ
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		//������������ֵ���õ�shader��
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		////������������ֵ���õ�shader��
		//glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//������������ֵ���õ�shader��
		glEnableVertexAttribArray(3);
	#pragma endregion



	#pragma region Init and Load Textures
		unsigned int texBufferA;
		texBufferA = LoadImageToGPU("container.jpg",GL_RGB,GL_RGB,0);
		unsigned int texBufferB;
		texBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
	#pragma endregion


	#pragma region Prepare MVP Matrices
		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projMat;
		//ͶӰ�任���������ӽǴ�С�����ݱȣ����ü��棬Զ�ü���(������γ����Ͳü�)
		projMat = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);
	#pragma endregion


	//===================��Ⱦѭ��==================================================
	//�������û�йر�
	while (!glfwWindowShouldClose(window))
	{

		//Process Input
		processInput(window);

		//Clear Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//�����ɫ���������Ȼ���
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

		viewMat = camera.GetViewMatrix();

		for (size_t i = 0; i < 10; i++)
		{
			//Set Model Matrix
			modelMat = glm::translate(glm::mat4(1.0f)/*��λ����*/,cubePositions[i]);//λ��

			//Set View and Projection Matrices here if you want.

			//Set Material -> Shader Program===============
			myShader->use();

			//Set Material -> Textures=====================
			//���������
			glActiveTexture(GL_TEXTURE0);
			//������A
			glBindTexture(GL_TEXTURE_2D, texBufferA);
			//���������
			glActiveTexture(GL_TEXTURE1);
			//������B
			glBindTexture(GL_TEXTURE_2D, texBufferB);

			//Set Material -> Uniforms=====================
			//���ľ����ֵ�����������ĵı���λ�ã������������Ƿ�Ծ���ת�ã������ľ������ݣ���Ҫͨ��glm::value_ptr(trans)����ת��Ϊopengl�ܽ��ܵ�ֵ��	
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(myShader->ID,"objColor"),1.0f,0.5f,0.31f);
			glUniform3f(glGetUniformLocation(myShader->ID,"ambientColor"),1.0f,1.0f,1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID,"lightPos"),10.0f,10.0f,5.0f);
			glUniform3f(glGetUniformLocation(myShader->ID,"lightColor"),1.0f,1.0f,1.0f);
			//Set Model====================================
			glBindVertexArray(VAO);

			//Draw Call====================================
			//����������,����1��Ҫ�������ͣ�����2������������ʼ������3������������
			glDrawArrays(GL_TRIANGLES, 0, 36);//ÿ����һ�Σ����ǽ���һ��DrawCall
		}

		//Clean up,propare for next render loop===============================
		//ת��ǰ��Buffer
		glfwSwapBuffers(window);
		//��ȡ�¼�
		glfwPollEvents();
		//�������������WS��ǰ���ƶ��ķ���
		camera.UpdateCameraPos();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Exit program=================================================
	//����ڴ�
	glfwTerminate();
	return 0;
}

