//头文件声明========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//系统自带的头文件用<>，项目下的头文件用""

//模型顶点数据=======================================================================
float vertices[] = {
	 -1, -1, 0.0f,1,0,0,		//0
	 -0.5f, 0.5f, 0.0f,0,1,0,	//1
	 0.5f,  -0.5f, 0.0f,0,0,1,//2
	 //-0.5f, 0.5f, 0.0f,
	 //0.5f,  -0.5f, 0.0f,
     1, 1, 0.0f,0.2f,0.3f,0.7f			//3

	////左下角
	//-1,-1,0, 1,0,0,//0
	//0,-1,0,0, 1,0,//1
	//-1,0,0, 0,0,1,//2
	////右下角
	//0,-1,0,0,0,1,
	//1,-1,0, 1,0,0,//3
	//1,0,0, 0,1,0,//4
	////右上角
	//1,0,0, 0,0,1,//5
	//1,1,0, 1,0,0,//6
	//0,1,0, 0,1,0,//7
	////左上角
	//0,1,0,0,0,1,
	//-1,1,0, 1,0,0,//8
	//-1,0,0,0,1,0

};
//用索引表示一个三角面：0，1，2    2，1，3.可以减少相同顶点的输入

unsigned int indices[] = {//注意索引从0开始
	0,1,2,//第一个三角形
	1,2,3 //第二个三角形
	//0,1,2,
	//1,3,4,
	//5,6,7,
	//7,8,2
};

//按下ESC关闭窗口====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}
}

//======================顶点着色器GLSL==============================================
//const char* vertexShaderSource =
//"#version 330 core										 \n"
//"layout (location = 0) in vec3 aPos;                     \n"
//"layout (location = 1) in vec3 aColor;                     \n"
//"out vec4 vertexColor;                                   \n"
//"void main(){                                            \n"
//"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);    \n"
//"    vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0);                    \n"
//"}   \n";
//=======================片段着色器GLSL=============================================
//const char* fragmentShaderSource =
//"#version 330 core								 \n"
//"out vec4 FragColor;							 \n"
//"in  vec4 vertexColor;							 \n"
//"uniform vec4 ourColor;							 \n"
//"void main(){                                    \n"
//"    FragColor = vertexColor;                 }  \n";

int main2()
{
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
	//框线模式
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//====================背面剔除===========================================
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);//opengl规定逆时针绘制三角形的正面
	//=====================VAO===============================================

	//Shader testShader = Shader("vertexSource.txt","fragmentSource.txt");
	//testShader.test();//对象配合.使用
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");
	//testShader->test();//指针配合->使用

	unsigned int VAO;//Vertex Array Object
	//生成一个VAO
	glGenVertexArrays(1,&VAO);
	//绑定
	glBindVertexArray(VAO);
	//=====================VBO===============================================
	unsigned int VBO;//Vertex Buffer Object
	//生成一个VBO
	glGenBuffers(1,&VBO);
	//从ARRAY_BUFFER绑上VAO了
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	//传递数据通过ARRAY_BUFFER传给VAO.参数1：传递的目标，参数2:数据的尺寸，参数3：数据，参数4：绘制的数据是否常变
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//=====================EBO================================================
	unsigned int EBO;//索引缓冲对象
	//生成一个EBO
	glGenBuffers(1,&EBO);
	//绑定EBO到GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	//往GL_ELEMENT_ARRAY_BUFFER中传入数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	////===================顶点着色器============================================
	////顶点着色器操作
	//unsigned int vertexShader;
	////创建一个VertexShader
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////将源文件赋值给VertexShader
	//glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	////编译VertexShader
	//glCompileShader(vertexShader);
	////====================片段着色器===========================================
	////片段着色器操作
	//unsigned int fragmentShader;
	////创建一个fragmentShader
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	////将源文件赋值给fragmentShader
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	////编译fragmentShader
	//glCompileShader(fragmentShader);
	////====================着色程序=============================================
	////把shader贴到shaderProgram
	//unsigned int shaderProgram;
	////生成一个shaderProgrma
	//shaderProgram = glCreateProgram();
	////将VertexShader和FragmentShader贴到ShaderProgram
	//glAttachShader(shaderProgram,vertexShader);
	//glAttachShader(shaderProgram,fragmentShader);
	////链接到ShaderProgram
	//glLinkProgram(shaderProgram);

	//顶点特征值，参数1：从哪里开始，参数2：一次塞多少，参数3：都是什么类型的顶点，
	//参数4：是否正规化到±1之间，参数5：每次获取顶点间隔多少，参数6：第一次获取从偏移多少的地方开始
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)0);
	//开启顶点特征值，用到shader中
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	//开启顶点特征值，用到shader中
	glEnableVertexAttribArray(1);

	//===================渲染循环==================================================
	//如果窗口没有关闭
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		////获取时间
		//float timeValue = glfwGetTime();
		////让timeColor的值映射到0到1之间
		//float changeTimeValue = (sin(5*timeValue) / 2.0f) + 0.5f;
		////获取shaderProgram中的ourColor
		//int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
		////使用程序
		//glUseProgram(shaderProgram);
		////给ourColor赋值
		//glUniform4f(vertexColorLocation, (sin(5 * timeValue) / 2.0f) + 0.5f, (sin(5 * timeValue + 0.5f) / 2.0f) + 0.5f, (sin(5 * timeValue + 1.0f) / 2.0f) + 0.5f, 1.0f);
	
		myShader->use();

		//画个三角面,参数1：要画的类型，参数2：从索引几开始，参数3：画几个索引
		//glDrawArrays(GL_TRIANGLES,0,12);
		//通过索引画出来，参数：画的类型，尺寸，都是什么类型，偏移值
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		//转换前后Buffer
		glfwSwapBuffers(window);
		//获取事件
		glfwPollEvents();
	}

	//清除内存
	glfwTerminate();

	return 0;
}

