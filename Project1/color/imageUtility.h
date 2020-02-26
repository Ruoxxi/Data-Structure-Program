#ifndef IMAGE_UTILILITY_H
#define IMAGE_UTILILITY_H

#include "FreeImage.h"

#pragma comment(lib, "./Lib/FreeImage.lib") //FreeImage.lib��Ҫ������ȷ��λ��
struct rl {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int numbers = 0;
	rl* next;
};//�洢�γ̱��������
struct SPixel //�洢���ص�RGB����������ע��ÿ��������unsigned char���ͣ�ȡֵ��Χ��[0, 255]
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct SImage
{
	SPixel** pixels;     //ͼ������ش洢�ڶ�ά�����У�����pixels[x][y]��ʾͼ��������(x,y)λ�õ�����
	unsigned int width;  //ͼ����
	unsigned int height; //ͼ��߶�
};

//���ļ���ȡTIFFͼ�����ݵ��ڴ棬ͼ�����ݴ洢�ڽṹ��SImage��
SImage readTIFFImageFromFile(const char* vFilePath);

//��ͼ�����ݴ��ڴ�д��������ΪTIFFͼ���ļ�
void writeTIFFImageToFile(const SImage& vImage, const char* vFilePath);

//�ͷ�SImage���������ݵ��ڴ�
void freeImageData(SImage& vImage);

//������ֵת��Ϊ��ɫ����ֵ
short energy2gray(long vMag);
void Record(rl* r, SImage* x);
void BoxBlur(SImage* x,int times);//ͼ��ģ��ͷ�ļ�
void Sobol(SImage* x, int times);//��Ե���ͷ�ļ�
void Writerl(SImage* x,char* file,rl* r);
void rrl(const char* file, SImage* x);
#endif
