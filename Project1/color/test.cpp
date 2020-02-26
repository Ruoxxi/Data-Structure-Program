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
		printf("请输入选项\n1.图像模糊\n2.边缘检测\n3.游程编码写入\n4.游程编码读取\n");
		scanf("%d",&i);
		if (i==1)
		{
		   printf("请输入执行次数：\n");
		   scanf("%d", &times);
		   printf("请带后缀直接输入./Res/目录下的图片名称，如engine.tiff，如果没有相应文件将报错\n");
           scanf("%s", fileinput);
	       strcat(file, fileinput);
		   printf("请带后缀直接输入你要保存的图片的名字，将保存在./Out/下，如baby.tiff,如果执行次数输入过长请等待\n");
		   scanf("%s", fileo);
		   strcat(fileoutput, fileo);
		   SImage testImage = readTIFFImageFromFile(file);
		   BoxBlur(&testImage, times);
		   printf("修改成功\n");
		   //保存TIFF图像到文件
		   writeTIFFImageToFile(testImage, fileoutput);
		   //释放图像内存
		   freeImageData(testImage);
		}
		if (i==2)
		{
		   printf("请输入执行次数：\n");
		   scanf("%d", &times);
		   printf("请带后缀直接输入./Res/目录下的图片名称，如engine.tiff，如果没有相应文件将报错\n");
		   scanf("%s", fileinput);
		   strcat(file, fileinput);
		   printf("请带后缀直接输入你要保存的图片的名字，将保存在./Out/下，如baby.tiff，如果执行次数输入过长请等待\n");
		   scanf("%s", fileo);
	       strcat(fileoutput, fileo);
		   SImage testImage = readTIFFImageFromFile(file);
		   Sobol(&testImage, times);
		   printf("修改成功\n");
		   //保存TIFF图像到文件
		   writeTIFFImageToFile(testImage, fileoutput);
		   //释放图像内存
		   freeImageData(testImage);
		}
		if (i == 3)
		{
			printf("请带后缀直接输入./Res/目录下的图片名称，如engine.tiff，如果没有相应文件将报错\n");
			scanf("%s", fileinput);
			strcat(file, fileinput);
			printf("请带后缀直接输入你要保存为游程编码的图片的名字，将保存在./Rl/下，如baby.txt\n");
			scanf("%s", filerl);
			strcat(filerloutput, filerl);
			SImage testImage = readTIFFImageFromFile(file);
			rl r;
			Record(&r, &testImage);
			Writerl(&testImage,filerloutput,&r);
			printf("保存成功\n");
			//保存游程编码到文件
			//释放图像内存
			freeImageData(testImage);
		}
		if (i == 4)
		{
			SImage testImage;
			printf("请带后缀直接输入./Rl/目录下的txt文件名称，如engine.txt,如果没有相应文件将报错\n");
			scanf("%s", filerl);
			strcat(filerloutput, filerl);
			printf("请带后缀直接输入转化为图片的txt文件的名字，将保存在./Out/下，如baby.tiff\n");
			scanf("%s", fileo);
			strcat(fileoutput, fileo);
			rrl(filerloutput, &testImage);
			writeTIFFImageToFile(testImage,fileoutput);
			printf("修改成功\n");
			//保存游程编码到文件
			//释放图像内存
			freeImageData(testImage);
		}
	system("pause");
	return 0;
}
