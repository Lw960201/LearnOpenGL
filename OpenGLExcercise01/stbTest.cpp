#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int main(){

	int width, height, nrChannels;//图宽，图高，通道
	stbi_set_flip_vertically_on_load(true);//opengl一般都是从底部开始绘制，而图片的坐标一般都是从顶部开始，加上这句话实现反转y轴
	unsigned char *data = stbi_load("pic.png", &width, &height, &nrChannels, 0);

	for (size_t i = 0; i < 50; i++)
	{
		printf("%d",(int)data[i]);
		//cout << (int)data[i] << endl;
	}

	stbi_image_free(data);
	
	while (true)
	{

	}

	return 0;
}