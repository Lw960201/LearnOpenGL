//头文件声明========================================================================
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"//系统自带的头文件用<>，项目下的头文件用""
//====对图片操作的api============
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//模型顶点数据=======================================================================
float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上

};
//用索引表示一个三角面：0，1，2    2，1，3.可以减少相同顶点的输入

unsigned int indices[] = {//注意索引从0开始
	0,1,3,//第一个三角形
	2,3,1 //第二个三角形
};

//按下ESC关闭窗口====================================================================
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwWindowShouldClose(window);
	}
}


int main()
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


	//================配置顶点特征值：如顶点位置，顶点颜色，纹理坐标==============================================
	//顶点特征值，参数1：从哪里开始，参数2：一次塞多少，参数3：都是什么类型的顶点，
	//参数4：是否正规化到±1之间，参数5：每次获取顶点间隔多少，参数6：第一次获取从偏移多少的地方开始
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
	//开启顶点特征值，用到shader中
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//开启顶点特征值，用到shader中
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//开启顶点特征值，用到shader中
	glEnableVertexAttribArray(2);

	//====================TEXTURE_2D_BUFFER============================================
    //生成一个texBuffer
	unsigned int texBufferA;
	glGenTextures(1, &texBufferA);
	//绑定，让之后的纹理命令都可以配置当前绑定的纹理
	glBindTexture(GL_TEXTURE_2D, texBufferA);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//放入原图============================================================================
	int width, height, nrChannels;//图宽，图高，颜色通道
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	//如果有数据
	if (data)
	{
		//渲染图片
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0/*是否要边缘*/, GL_RGB, GL_UNSIGNED_BYTE, data);
		//绑定在GL_TEXTURE_2D上的图，给他生成mipmap，必须要
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//用完内存后释放内存
	stbi_image_free(data);

	//生成一个texBuffer
	unsigned int texBufferB;
	glGenTextures(1, &texBufferB);
	glActiveTexture(GL_TEXTURE1);
	//绑定，让之后的纹理命令都可以配置当前绑定的纹理
	glBindTexture(GL_TEXTURE_2D, texBufferB);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//放入原图============================================================================
	//int width, height, nrChannels;//图宽，图高，颜色通道
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	//如果有数据
	if (data)
	{
		//渲染图片
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0/*是否要边缘*/, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//绑定在GL_TEXTURE_2D上的图，给他生成mipmap，必须要
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Load Image Failed.");
	}
	//用完内存后释放内存
	stbi_image_free(data);

	myShader->use();
	glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);

	//===================渲染循环==================================================
	//如果窗口没有关闭
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texBufferB);

		myShader->use();
		glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	

		//画个三角面,参数1：要画的类型，参数2：从索引几开始，参数3：画几个索引
		//glDrawArrays(GL_TRIANGLES,0,12);
		//通过索引画出来，参数：画的类型，尺寸，都是什么类型，偏移值
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		//转换前后Buffer
		glfwSwapBuffers(window);
		//获取事件
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//清除内存
	glfwTerminate();

	return 0;
}

