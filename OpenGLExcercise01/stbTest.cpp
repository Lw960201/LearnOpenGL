#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int main(){

	int width, height, nrChannels;//ͼ��ͼ�ߣ�ͨ��
	stbi_set_flip_vertically_on_load(true);//openglһ�㶼�Ǵӵײ���ʼ���ƣ���ͼƬ������һ�㶼�ǴӶ�����ʼ��������仰ʵ�ַ�תy��
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