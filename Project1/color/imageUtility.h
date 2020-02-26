#ifndef IMAGE_UTILILITY_H
#define IMAGE_UTILILITY_H

#include "FreeImage.h"

#pragma comment(lib, "./Lib/FreeImage.lib") //FreeImage.lib需要放在正确的位置
struct rl {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int numbers = 0;
	rl* next;
};//存储游程编码的链表
struct SPixel //存储像素的RGB三个分量，注意每个分量是unsigned char类型，取值范围是[0, 255]
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct SImage
{
	SPixel** pixels;     //图像的像素存储在二维数组中，例如pixels[x][y]表示图像中坐标(x,y)位置的像素
	unsigned int width;  //图像宽度
	unsigned int height; //图像高度
};

//从文件读取TIFF图像数据到内存，图像数据存储在结构体SImage中
SImage readTIFFImageFromFile(const char* vFilePath);

//将图像数据从内存写出，保存为TIFF图像文件
void writeTIFFImageToFile(const SImage& vImage, const char* vFilePath);

//释放SImage中像素数据的内存
void freeImageData(SImage& vImage);

//将能量值转换为灰色像素值
short energy2gray(long vMag);
void Record(rl* r, SImage* x);
void BoxBlur(SImage* x,int times);//图像模糊头文件
void Sobol(SImage* x, int times);//边缘检测头文件
void Writerl(SImage* x,char* file,rl* r);
void rrl(const char* file, SImage* x);
#endif
