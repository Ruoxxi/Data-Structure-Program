#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageUtility.h"
int main()
{
	int i;
	int times;
	char file[100] = "./Res/";
	char fileinput[100];
	char fileo[100];
	char fileoutput[100] = "./Out/";
	char filerl[100];
	char filerloutput[100] = "./Rl/";
		printf("������ѡ��\n1.ͼ��ģ��\n2.��Ե���\n3.�γ̱���д��\n4.�γ̱����ȡ\n");
		scanf("%d",&i);
		if (i==1)
		{
		   printf("������ִ�д�����\n");
		   scanf("%d", &times);
		   printf("�����׺ֱ������./Res/Ŀ¼�µ�ͼƬ���ƣ���engine.tiff�����û����Ӧ�ļ�������\n");
           scanf("%s", fileinput);
	       strcat(file, fileinput);
		   printf("�����׺ֱ��������Ҫ�����ͼƬ�����֣���������./Out/�£���baby.tiff,���ִ�д������������ȴ�\n");
		   scanf("%s", fileo);
		   strcat(fileoutput, fileo);
		   SImage testImage = readTIFFImageFromFile(file);
		   BoxBlur(&testImage, times);
		   printf("�޸ĳɹ�\n");
		   //����TIFFͼ���ļ�
		   writeTIFFImageToFile(testImage, fileoutput);
		   //�ͷ�ͼ���ڴ�
		   freeImageData(testImage);
		}
		if (i==2)
		{
		   printf("������ִ�д�����\n");
		   scanf("%d", &times);
		   printf("�����׺ֱ������./Res/Ŀ¼�µ�ͼƬ���ƣ���engine.tiff�����û����Ӧ�ļ�������\n");
		   scanf("%s", fileinput);
		   strcat(file, fileinput);
		   printf("�����׺ֱ��������Ҫ�����ͼƬ�����֣���������./Out/�£���baby.tiff�����ִ�д������������ȴ�\n");
		   scanf("%s", fileo);
	       strcat(fileoutput, fileo);
		   SImage testImage = readTIFFImageFromFile(file);
		   Sobol(&testImage, times);
		   printf("�޸ĳɹ�\n");
		   //����TIFFͼ���ļ�
		   writeTIFFImageToFile(testImage, fileoutput);
		   //�ͷ�ͼ���ڴ�
		   freeImageData(testImage);
		}
		if (i == 3)
		{
			printf("�����׺ֱ������./Res/Ŀ¼�µ�ͼƬ���ƣ���engine.tiff�����û����Ӧ�ļ�������\n");
			scanf("%s", fileinput);
			strcat(file, fileinput);
			printf("�����׺ֱ��������Ҫ����Ϊ�γ̱����ͼƬ�����֣���������./Rl/�£���baby.txt\n");
			scanf("%s", filerl);
			strcat(filerloutput, filerl);
			SImage testImage = readTIFFImageFromFile(file);
			rl r;
			Record(&r, &testImage);
			Writerl(&testImage,filerloutput,&r);
			printf("����ɹ�\n");
			//�����γ̱��뵽�ļ�
			//�ͷ�ͼ���ڴ�
			freeImageData(testImage);
		}
		if (i == 4)
		{
			SImage testImage;
			printf("�����׺ֱ������./Rl/Ŀ¼�µ�txt�ļ����ƣ���engine.txt,���û����Ӧ�ļ�������\n");
			scanf("%s", filerl);
			strcat(filerloutput, filerl);
			printf("�����׺ֱ������ת��ΪͼƬ��txt�ļ������֣���������./Out/�£���baby.tiff\n");
			scanf("%s", fileo);
			strcat(fileoutput, fileo);
			rrl(filerloutput, &testImage);
			writeTIFFImageToFile(testImage,fileoutput);
			printf("�޸ĳɹ�\n");
			//�����γ̱��뵽�ļ�
			//�ͷ�ͼ���ڴ�
			freeImageData(testImage);
		}
	system("pause");
	return 0;
}
