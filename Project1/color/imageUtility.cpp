#include "imageUtility.h"
#include "FreeImage.h"
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>

SImage readTIFFImageFromFile(const char* vFilePath)
{
	assert(vFilePath);

	FIBITMAP* pFIBitmap = FreeImage_Load(FIF_TIFF, vFilePath, 0);
	assert(pFIBitmap);

	unsigned int width = FreeImage_GetWidth(pFIBitmap);
	unsigned int height = FreeImage_GetHeight(pFIBitmap);
	assert(width > 0 && height > 0);

	SImage image;
	image.width = width;
	image.height = height;

	image.pixels = (SPixel**)malloc(width * sizeof(SPixel*));
	for (unsigned int i = 0; i < width; ++i)
		image.pixels[i] = (SPixel*)malloc(height * sizeof(SPixel));

	for (unsigned int x = 0; x < width; ++x)
	{
		for (unsigned int y = 0; y < height; ++y)
		{
			RGBQUAD rgbQuad;
			FreeImage_GetPixelColor(pFIBitmap, x, y, &rgbQuad);
			image.pixels[x][y].red = rgbQuad.rgbRed;
			image.pixels[x][y].green = rgbQuad.rgbGreen;
			image.pixels[x][y].blue = rgbQuad.rgbBlue;
		}
	}

	FreeImage_Unload(pFIBitmap);

	return image;
}

void writeTIFFImageToFile(const SImage& vImage, const char* vFilePath)
{
	assert(vImage.pixels && vImage.width > 0 && vImage.height > 0 && vFilePath);

	FIBITMAP* pFIBitmap = FreeImage_Allocate(vImage.width, vImage.height, 24);
	assert(pFIBitmap);

	for (unsigned int x = 0; x < vImage.width; ++x)
	{
		for (unsigned int y = 0; y < vImage.height; ++y)
		{
			RGBQUAD rgbQuad;
			rgbQuad.rgbRed = vImage.pixels[x][y].red;
			rgbQuad.rgbGreen = vImage.pixels[x][y].green;
			rgbQuad.rgbBlue = vImage.pixels[x][y].blue;
			FreeImage_SetPixelColor(pFIBitmap, x, y, &rgbQuad);
		}
	}

	FreeImage_Save(FIF_TIFF, pFIBitmap, vFilePath, 0);
	FreeImage_Unload(pFIBitmap);
}

void freeImageData(SImage& vImage)
{
	for (int i = 0; i < vImage.width; ++i)
		free(vImage.pixels[i]);
	free(vImage.pixels);
	vImage.pixels = NULL;
}

short energy2gray(long vMag)
{
	short intensity = (short)(30.0 * log(1.0 + (double)vMag) - 256.0);

	if (intensity < 0) intensity = 0;
	else if (intensity > 255) intensity = 255;

	return intensity;
}

void BoxBlur(SImage *x, int times) {//times为图像模糊执行的次数
	SPixel** p;
	p = (SPixel * *)malloc((x->width) * sizeof(SPixel*));//由于直接对x进行操作会引起内存问题，这里考虑设置临时的SPixel**并为它分配内存
	for (int i = 0; i < x->width; i++)
		p[i] = (SPixel*)malloc((x->height) * sizeof(SPixel));//一共为p分配了x->width*x->height个可以放得下像素的三个分量的内存
	for (int time = 0; time < times; time++)
	{
		for (int i = 0; i < x->width; i++)//将x->pixels拷贝到p
		{
			for (int j = 0; j < x->height ; j++)
			{
					p[i][j] = x->pixels[i][j];
			}
		}
		for (int i = 0; i < x->width; i++)//分情况对p进行图像模糊操作
		{
			for (int j = 0; j < x->height; j++)
			{
				int r = 0, g = 0, b = 0;
				if (i == 0 || j == 0 || i == x->width - 1 || j == x->height - 1) {//p为边缘的像素的情况,包括p为角落的点上和边线上的像素两种情况
					if ((i == 0 && j ==0)) {
						r = (int)p[i][j].red + (int)p[i+1][j+1].red + (int)p[i+1][j].red + (int)p[i][j+1].red;
						g = (int)p[i][j].green + (int)p[i+1][j+1].green + (int)p[i+1][j].green + (int)p[i][j+1].green;
						b = (int)p[i][j].blue + (int)p[i+1][j+1].blue + (int)p[i+1][j].blue + (int)p[i][j+1].blue;
						r = r / 4;
						g = g / 4;
						b = b / 4;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
				    }
					if ((i == x->width-1 && j == 0)) {
						r = (int)p[i][j].red + (int)p[i - 1][j + 1].red + (int)p[i - 1][j].red + (int)p[i][j - 1].red;
						g = (int)p[i][j].green + (int)p[i - 1][j + 1].green + (int)p[i - 1][j].green + (int)p[i][j - 1].green;
						b = (int)p[i][j].blue + (int)p[i - 1][j + 1].blue + (int)p[i - 1][j].blue + (int)p[i][j - 1].blue;
						r = r / 4;
						g = g / 4;
						b = b / 4;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((i == 0 && j == x->height-1)) {
						r = (int)p[i][j].red + (int)p[i + 1][j - 1].red + (int)p[i + 1][j].red + (int)p[i][j - 1].red;
						g = (int)p[i][j].green + (int)p[i + 1][j - 1].green + (int)p[i + 1][j].green + (int)p[i][j - 1].green;
						b = (int)p[i][j].blue + (int)p[i + 1][j - 1].blue + (int)p[i + 1][j].blue + (int)p[i][j - 1].blue;
						r = r / 4;
						g = g / 4;
						b = b / 4;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((i == x->width-1 && j == x->height-1)) {
						r = (int)p[i][j].red + (int)p[i - 1][j - 1].red + (int)p[i - 1][j].red + (int)p[i][j - 1].red;
						g = (int)p[i][j].green + (int)p[i - 1][j - 1].green + (int)p[i - 1][j].green + (int)p[i][j - 1].green;
						b = (int)p[i][j].blue + (int)p[i - 1][j - 1].blue + (int)p[i - 1][j].blue + (int)p[i][j - 1].blue;
						r = r / 4;
						g = g / 4;
						b = b / 4;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((i == x->width - 1 && j != x->height - 1&& j != 0)) {
						for ( int m = -1;  m < 1; m++)
						{
							r += (int)p[i][j + m].red + (int)p[i - 1][j + m].red;
							g += (int)p[i][j + m].green + (int)p[i - 1][j + m].green;
							b += (int)p[i][j + m].blue + (int)p[i - 1][j + m].blue;
						}
						r = r / 6;
						g = g / 6;
						b = b / 6;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((i == 0 && j != x->height - 1 && j != 0)) {
						for (int m = -1; m < 1; m++)
						{
							r += (int)p[i][j + m].red + (int)p[i + 1][j + m].red;
							g += (int)p[i][j + m].green + (int)p[i + 1][j + m].green;
							b += (int)p[i][j + m].blue + (int)p[i + 1][j + m].blue;
						}
						r = r / 6;
						g = g / 6;
						b = b / 6;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((j == x->width - 1 && i != x->height - 1 && i != 0)) {
						for (int m = -1; m < 1; m++)
						{
							r += (int)p[i+m][j].red + (int)p[i+m][j-1].red;
							g += (int)p[i+m][j].green + (int)p[i+m][j-1].green;
							b += (int)p[i+m][j].blue + (int)p[i+m][j-1].blue;
						}
						r = r / 6;
						g = g / 6;
						b = b / 6;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
					if ((j == 0 && i != x->height - 1 && i != 0)) {
						for (int m = -1; m < 1; m++)
						{
							r += (int)p[i + m][j].red + (int)p[i + m][j + 1].red;
							g += (int)p[i + m][j].green + (int)p[i + m][j + 1].green;
							b += (int)p[i + m][j].blue + (int)p[i + m][j + 1].blue;
						}
						r = r / 6;
						g = g / 6;
						b = b / 6;
						x->pixels[i][j].red = (unsigned char)r;
						x->pixels[i][j].green = (unsigned char)g;
						x->pixels[i][j].blue = (unsigned char)b;
					}
				}
				else//p为中间像素的情况
				{
                    for (int m = -1; m < 2; m++)
		     		{
					for (int n = -1; n < 2; n++)//直接使用unsigned char进行加法运算图像会变黑，这里使用强制类型转换为int进行运算再转换回unsigned char
				    	{
						    r += (int)p[i + m][j + n].red;
							g += (int)p[i + m][j + n].green;
							b += (int)p[i + m][j + n].blue;
					     }
				    }
				    r = r / 9;
				    g = g / 9;
				    b = b / 9;
				    x->pixels[i][j].red = (unsigned char)r;
				    x->pixels[i][j].green = (unsigned char)g;
				    x->pixels[i][j].blue = (unsigned char)b;
				}
				
			}
		}
	}
}
void Sobol(SImage* x, int times) {
	BoxBlur(x, times);//边缘检测前通常要引用图像模糊
	long** energy;//对energy使用long **来定义，便于使用malloc为energy[]分配内存
	long xr = 0, xg = 0, xb = 0, yr = 0, yg = 0, yb = 0;//它们分别代表x,y的r,g,b的带权相加的结果
	int qx[3][3] = { 1,0,-1,2,0,-2,1,0,-1 };
    int qy[3][3] = { 1,2,1,0,0,0,-1,-2,-1 };//qx和qy用作计算梯度时x和y带权相加时的权
	energy = (long**)malloc(x->width * sizeof(long*));
	for (int i = 0; i < x->width; i++) {
		energy[i] = (long*)malloc(x->height * sizeof(long));
	}//为每个像素块分配一个long类型大小的内存空间用来储存energy(x,y)
	for (int i = 0; i < x->width; i++)
	{
		for (int j = 0; j < x->height; j++)
		{
			for (int m = 0; m < 3; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					int xi = i - 1 + n;
					int yj = j - 1 + m;
					if (xi < 0)
					{
						xi = 0;
					}
					if (xi == x->width)
					{
						xi = x->width - 1;
					}
					if (yj < 0)
					{
						yj = 0;
					}
					if (yj == x->height)
					{
						yj = x->height - 1;
					}//特殊考虑图像边界的情况，为边界外赋值
					xr += qx[m][n] * (long)x->pixels[xi][yj].red;
					xg += qx[m][n] * (long)x->pixels[xi][yj].green;
					xb += qx[m][n] * (long)x->pixels[xi][yj].blue;
					yr += qy[m][n] * (long)x->pixels[xi][yj].red;
					yg += qy[m][n] * (long)x->pixels[xi][yj].green;
					yb += qy[m][n] * (long)x->pixels[xi][yj].blue;
				}
			}
			energy[i][j] = xr * xr + xg * xg + xb * xb + yr * yr + yg * yg + yb * yb;
			xr = 0, xg = 0, xb = 0, yr = 0, yg = 0, yb = 0;
		}

	}
	for (int i = 0; i < x->width; i++)
	{
		for (int j = 0; j < x->height; j++)
		{
			int pix = energy2gray(energy[i][j]);
			x->pixels[i][j].red = (unsigned char)pix;
			x->pixels[i][j].green = (unsigned char)pix;
			x->pixels[i][j].blue = (unsigned char)pix;
		}
	}

}
void Record(rl* r, SImage* x) {//将TIFF文件进行游程编码
	rl* head = r;//标记链表的头部

	for (int i = 0; i < x->width; i++)
	{
		for (int j = 0; j < x->height; j++)
		{
			if (r->r == x->pixels[i][j].red && r->g == x->pixels[i][j].green && r->b == x->pixels[i][j].blue)
			{//当tiff文件相邻的像素的rsb都相同时，链表中的numbers+1
				r->numbers = r->numbers + 1;
			}
			else {
				r->next = (rl*)malloc(sizeof(rl));
				r = r->next;
				r->next = NULL;
				r->r = x->pixels[i][j].red;
				r->g = x->pixels[i][j].green;
				r->b = x->pixels[i][j].blue;
				r->numbers = 1;
			}
		}
	}
	r = head;
}
void Writerl(SImage* x,char* file,rl* r) {//将游程编码写入文件
	FILE* fp;
	fp = fopen(file, "w");
	fprintf(fp, "%d %d\n", x->width, x->height);
	r = r->next;
	while (r != NULL)
	{
		int out = (r->r << 16) + (r->g << 8) + (r->b);
		fprintf(fp, "-%08d%d", out, r->numbers);
		r = r->next;
	}
	fclose(fp);
}

void rrl(const char* file, SImage* x) {//读取游程编码
	FILE* fp;
	fp = fopen(file, "r");
	rl* head = (rl*)malloc(sizeof(rl));
	rl* p;
	head->next = (rl*)malloc(sizeof(rl));
	p = head->next;
	p->next = NULL;
	fscanf(fp, "%d %d\n", &(x->width), &(x->height));
	int output;
	x->pixels = (SPixel * *)malloc(x->width * sizeof(SPixel*));
	for (int i = 0; i < x->width; i++) {
		x->pixels[i] = (SPixel *)malloc(x->height * sizeof(SPixel));
	}
	for (int i = 0;fscanf(fp, "-%8d%d", &output, &(p->numbers)) != -1;i++)
	{
		p->b = (unsigned char)output;
		p->g = (unsigned char)(output >> 8);
		p->r = (unsigned char)(output >> 16);
		p->next = (rl*)malloc(sizeof(rl));
		p = p->next;
		p->next = NULL;
	}

	p = head->next;

	for (int i = 0; i < x->width; i++)
	{
		for (int j = 0; j < x->height; j++)
		{
			if (p->numbers == 0)
			{
				p = p->next;
			}

			x->pixels[i][j].red = p->r;
			x->pixels[i][j].green = p->g;
			x->pixels[i][j].blue = p->b;
			p->numbers=p->numbers-1;
		}
	}
	fclose(fp);
}

void readFile() {
	FILE *p;
	p = fopen("test.txt", "w");
}