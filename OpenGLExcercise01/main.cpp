//头文件声明========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//系统自带的头文件用<>，项目下的头文件用""
#include "Material.h"
//====对图片操作的api============
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>//跟opengl做互传的时候需要

#include "Camera.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

#include "Mesh.h"
#include "Model.h"

#pragma region Model Data
//一个Cube的顶点坐标
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

//多个cube的位置
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
//实例化摄像机
//Camera camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
LightDirectional lightD (glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f),0),
	glm::vec3(1.0f,1.0f,1.0f));

LightPoint lightP0 (glm::vec3(1.0f, 0, 0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f),0),
	glm::vec3(1.0f,0,0));
LightPoint lightP1 (glm::vec3(0, 1.0f, 0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0, 1.0f, 0));
LightPoint lightP2 (glm::vec3(0, 0, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0, 0, 1.0f));
LightPoint lightP3 (glm::vec3(-1.0f, 0,0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightSpot lightS (glm::vec3(0, 3, 0),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
	glm::vec3(1.0f, 1.0f, 0));
#pragma endregion

#pragma region Input Declare(声明)
//前一次的鼠标坐标
float lastX;
float lastY;
bool firstMouse = true;

//按下ESC关闭窗口====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
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

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SpeedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SpeedX = -1.0f;
	}
	else
	{
		camera.SpeedX = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.SpeedY= -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.SpeedY = 1.0f;
	}
	else
	{
		camera.SpeedY = 0;
	}
}

//鼠标回调方法必须参数是GLFWwindow*、double、double
void mouse_callback(GLFWwindow* window,double xPos,double yPos) {
	//避免首次偏移值太大
	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	//每次的偏移量
	float deltaX, deltaY;
	//与上一次鼠标位置的偏移量
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	//把这一次的鼠标坐标值赋值给上一次的鼠标坐标值
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
	//绑定，让之后的纹理命令都可以配置当前绑定的纹理
	glBindTexture(GL_TEXTURE_2D, texBuffer);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;//图宽，图高，颜色通道
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	//如果有数据
	if (data)
	{
		//渲染图片
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0/*是否要边缘*/, format, GL_UNSIGNED_BYTE, data);
		//绑定在GL_TEXTURE_2D上的图，给他生成mipmap，必须要
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//用完内存后释放内存
	stbi_image_free(data);

	return texBuffer;
}

int main(int argc,char* argv[])
{
	std::string exePath = argv[0];
	//std::cout << exePath.substr(0,exePath.find_last_of("\\")) + "\\model\\nanosuit.obj" << std::endl;

	#pragma region Open a Window

		//===================初始化====================================================
		//初始化glfw库
		glfwInit();
		//大版本号3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//小版本好3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		//可编程管线
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
		//======================窗口===================================================
		//创建 GLFW 窗口
		GLFWwindow* window = glfwCreateWindow(800,600,"My OpenGL Game",NULL,NULL);

		//如果是空则开窗失败
		if (window == NULL)
		{
			printf("Open Window Faild!");
			//不再运行
			glfwTerminate();
			return -1;
		}

		//window继续使用在上下文（继续使用window）
		glfwMakeContextCurrent(window);

		//关掉鼠标显示.参数：哪个窗口，鼠标类型，禁用鼠标
		glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
		//当鼠标移动时调用回调回调方法。参数：哪个窗口被监测，调用哪个方法
		glfwSetCursorPosCallback(window,mouse_callback);

		//初始化 GLEW
		glewExperimental = true;
		//如果初始化GLEW失败
		if (glewInit()!=GLEW_OK)
		{
			printf("Init GLEW Faild!");
			glfwTerminate();
			return -1;
		}

		glViewport(0,0,800,600);
		//开启深度测试
		glEnable(GL_DEPTH_TEST);
	#pragma endregion

	#pragma region Init Shader Program
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

	#pragma region Init Material
			Material* myMaterial = new Material(myShader,
				LoadImageToGPU("container2.png",GL_RGBA,GL_RGBA,Shader::DIFFUSE),
				LoadImageToGPU("container2_specular.png",GL_RGBA,GL_RGBA,Shader::SPECULAR),
				/*LoadImageToGPU("matrix.jpg",GL_RGB,GL_RGB,Shader::EMISSION),*/
				glm::vec3(1.0f,1.0f,1.0f),
				64.0f);
	#pragma endregion

	#pragma region Init and Load Models to VAO,VBO
			//Mesh cube(vertices);
			Model model(exePath.substr(0, exePath.find_last_of("\\")) + "\\model\\nanosuit.obj");
		//unsigned int VAO;//Vertex Array Object
		////生成一个VAO
		//glGenVertexArrays(1,&VAO);
		////绑定
		//glBindVertexArray(VAO);
		////=====================VBO===============================================
		//unsigned int VBO;//Vertex Buffer Object
		////生成一个VBO
		//glGenBuffers(1,&VBO);
		////从ARRAY_BUFFER绑上VAO了
		//glBindBuffer(GL_ARRAY_BUFFER,VBO);
		////传递数据通过ARRAY_BUFFER传给VAO.参数1：传递的目标，参数2:数据的尺寸，参数3：数据，参数4：绘制的数据是否常变
		//glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

		////================配置顶点特征值：如顶点位置，顶点颜色，纹理坐标==============================================
		////顶点特征值，参数1：从哪里开始，参数2：一次塞多少，参数3：都是什么类型的顶点，
		////参数4：是否正规化到±1之间，参数5：每次获取顶点间隔多少，参数6：第一次获取从偏移多少的地方开始
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		////开启顶点特征值，用到shader中
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		////开启顶点特征值，用到shader中
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		////开启顶点特征值，用到shader中
		//glEnableVertexAttribArray(2);
	#pragma endregion



	#pragma region Init and Load Textures
		/*unsigned int texBufferA;
		texBufferA = LoadImageToGPU("container.jpg",GL_RGB,GL_RGB,0);
		unsigned int texBufferB;
		texBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);*/
	#pragma endregion


	#pragma region Prepare MVP Matrices
		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projMat;
		//投影变换。参数：视角大小，横纵比，近裁剪面，远裁剪面(包括齐次除法和裁剪)
		projMat = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);
	#pragma endregion


	//===================渲染循环==================================================
	//如果窗口没有关闭
	while (!glfwWindowShouldClose(window))
	{

		//Process Input
		processInput(window);

		//Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//清除颜色缓存或者深度缓存
		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

		viewMat = camera.GetViewMatrix();

		for (size_t i = 0; i < 1; i++)
		{
			//Set Model Matrix
			modelMat = glm::translate(glm::mat4(1.0f)/*单位矩阵*/,cubePositions[i]);//位移

			//Set View and Projection Matrices here if you want.

			//Set Material -> Shader Program===============
			myShader->use();

			//Set Material -> Textures=====================
			/*glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);*/
			//glActiveTexture(GL_TEXTURE0 + 2);
			//glBindTexture(GL_TEXTURE_2D, myMaterial->emission);

			//Set Material -> Uniforms=====================
			//更改矩阵的值。参数：更改的变量位置，传几个矩阵，是否对矩阵转置，真正的矩阵数据（需要通过glm::value_ptr(trans)方法转换为opengl能接受的值）	
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform3f(glGetUniformLocation(myShader->ID,"objColor"),1.0f,1.0f,1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID,"ambientColor"),0.3f,0.3f,0.3f);

			glUniform3f(glGetUniformLocation(myShader->ID,"lightD.pos"),lightD.position.x,lightD.position.y,lightD.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID,"lightD.color"),lightD.color.x,lightD.color.y,lightD.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), lightD.direction.x, lightD.direction.y, lightD.direction.z);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadrtic"), lightP0.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadrtic"), lightP1.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadrtic"), lightP2.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadrtic"), lightP3.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z/*sin(glfwGetTime() * 2.0f) +0.5f, sin(glfwGetTime() * 5.0f)+0.5f, sin(glfwGetTime() * 10.0f)+0.5f*/);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadrtic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.constant"),light.constant);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.linear"),light.linear);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightP.quadratic"),light.quadratic);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightS.cosPhyInner"),light.cosPhyInner);
			//glUniform1f(glGetUniformLocation(myShader->ID,"lightS.cosPhyOutter"),light.cosPhyOutter);

			glUniform3f(glGetUniformLocation(myShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);

			myMaterial->shader->SetUniform3f("material.ambient",myMaterial->ambient);
			myMaterial->shader->SetUniform1i("material.diffuse",Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular",Shader::SPECULAR);
			//myMaterial->shader->SetUniform1i("material.emission",Shader::EMISSION);
			//myMaterial->shader->SetUniform3f("material.specular",myMaterial->specular);
			myMaterial->shader->SetUniform1f("material.shininess",myMaterial->shininess);
			//Set Model====================================
			//glBindVertexArray(VAO);

			//Draw Call====================================
			//画个三角面,参数1：要画的类型，参数2：从索引几开始，参数3：画几个索引
			//glDrawArrays(GL_TRIANGLES, 0, 36);//每调用一次，就是进行一次DrawCall

			//cube.Draw(myMaterial->shader);
			model.Draw(myMaterial->shader);
		}

		//Clean up,propare for next render loop===============================
		//转换前后Buffer
		glfwSwapBuffers(window);
		//获取事件
		glfwPollEvents();
		//调用摄像机按下WS键前后移动的方法
		camera.UpdateCameraPos();
	}

	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/

	// Exit program=================================================
	//清除内存
	glfwTerminate();
	return 0;
}

