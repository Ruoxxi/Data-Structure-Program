//#include "stdafx.h"
#include"CoorTrans.h"
#include<cmath>
#include<cstdio>
#include"CreateGraph1.h"


double distance1[25][25];
double distance2[25][25];
#define  www 1/0.0L
//��ȡ����֮��ľ���
int data()
{
	double x[25],y[25],lo[25],la[25];//x,yΪ������꣬laΪ���ȣ�loΪά��

    int road1[25][25];//�������޵�·
    int road2[25][25];//�ݳ����޵�·
    //double x1,y1,x2,y2,distance,lo1,la1,lo2,la2;
	for(int i=0;i<25;i++){
	    for(int j=0;j<25;j++){
	        distance1[i][j]=www;
	        distance2[i][j]=www;
	        road1[i][j]=0;
	        road2[i][j]=0;
	    }
	}
	PrjPoint point[25];
	for(int i=0;i<25;i++){
	    point[i]=PrjPoint();
	}
	//��γ������
	la[0]=103.998199;
	lo[0]=30.559455;
	la[1]=104.001487;
	lo[1]=30.560427;
	la[2]=104.003194;
	lo[2]=30.559191;
    la[3]=104.002469;
    lo[3]=30.558252;
    la[4]=104.006329;
    lo[4]=30.560921;
    la[5]=104.005822;
    lo[5]=30.560077;
    la[6]=104.006504;
    lo[6]=30.560423;
    la[7]=104.007084;
    lo[7]=30.560777;
    la[8]=104.009015;
    lo[8]=30.560590;
    la[9]=104.009640;
    lo[9]=30.560692;
    la[10]=104.010322;
    lo[10]=30.561554;
    la[11]=104.011113;
    lo[11]=30.561450;
    la[12]=104.010393;
    lo[12]=30.565197;
    la[13]=104.001870;
    lo[13]=30.561488;
    la[14]=104.008121;
    lo[14]=30.563803;
    la[15]=103.999346;
    lo[15]=30.561941;
    la[16]=104.010855;
    lo[16]=30.565392;
    la[17]=104.006277;
    lo[17]=30.562702;
    la[18]=104.012912;
    lo[18]=30.563747;
    la[19]=104.006358;
    lo[19]=30.564832;
    la[20]=104.004601;
    lo[20]=30.566817;
    la[21]=103.998194;
    lo[21]=30.563573;
    la[22]=104.002946;
    lo[22]=30.559653;
    la[23]=104.010403;
    lo[23]=30.567404;
    la[24]=103.999790;
    lo[24]=30.559284;
    //���������ڽӵ�·
    road1[0][13]=1;
    road1[0][15]=1;
    road1[0][21]=1;
    road1[0][24]=1;
    road1[1][3]=1;
    road1[1][5]=1;
    road1[1][13]=1;
    road1[1][17]=1;
    road1[1][21]=1;
    road1[1][22]=1;
    road1[1][24]=1;
    road1[2][3]=1;
    road1[2][5]=1;
    road1[2][22]=1;
    road1[3][13]=1;
    road1[3][22]=1;
    road1[3][24]=1;
    road1[4][5]=1;
    road1[4][6]=1;
    road1[4][6]=1;
    road1[4][17]=1;
    road1[4][18]=1;
    road1[5][6]=1;
    road1[5][7]=1;
    road1[6][7]=1;
    road1[7][8]=1;
    road1[8][9]=1;
    road1[9][10]=1;
    road1[10][11]=1;
    road1[12][14]=1;
    road1[12][16]=1;
    road1[12][18]=1;
    road1[12][23]=1;
    road1[13][15]=1;
    road1[13][21]=1;
    road1[13][22]=1;
    road1[14][19]=1;
    road1[15][20]=1;
    road1[15][21]=1;
    road1[16][18]=1;
    road1[17][18]=1;
    road1[17][19]=1;
    road1[20][21]=1;
    //�ݳ������ڽӵ�·
    road2[4][17]=1;
    road2[12][14]=1;
    road2[12][16]=1;
    road2[12][18]=1;
    road2[12][20]=1;
    road2[12][23]=1;
    road2[14][18]=1;
    road2[14][19]=1;
    road2[14][20]=1;
    road2[15][20]=1;
    road2[15][21]=1;
    road2[17][19]=1;
    road2[18][20]=1;
    //������·�޷���
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(road1[i][j]==1){
                road1[j][i]=1;
            }
            if(road2[i][j]==1){
                road2[j][i]=1;
            }
        }
    }
    for(int i=0;i<25;i++){
        road1[i][i]=1;
        road2[i][i]=1;
    }
    //��ȡ�������
    for(int i=0;i<25;i++){
        point[i].SetLoLa(lo[i],la[i]);
        point[i].Getxy(&x[i],&y[i]);
    }
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(road1[i][j]==1){
                distance1[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            }
            if(road2[i][j]==1){
                distance2[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
            }
        }
    }
	/*PrjPoin
	 * \\\\\\\\\\\\\\\\\\\\\\\\\\\\t point1=PrjPoint();
	PrjPoint point2=PrjPoint();
	lo1=30.6335;  //γ�� 
	la1=104.0665;  //����
	lo2=30.6499;  //γ�� 
	la2=104.0660;  //����
	point1.SetLoLa(lo1, la1);  //��1���� 
	point2.SetLoLa(lo2, la2);  //��2����

	point1.Getxy(&x1,&y1);  //�õ���1����Ĵ������ 
	point2.Getxy(&x2,&y2);  //�õ���2����Ĵ������

	distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	printf("������(%f,%f)(%f,%f)֮��ľ���Ϊ:%f��\n",lo1,la1,lo2,la2,distance);

	getchar();*/
}
//������֮��ľ������ͼ��
//1Ϊ����
void getData1(Graph* G){
    data();
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(distance1[i][j]!=www){
                //printf("%f\n",distance1[i][j]);
                G->setEdge(i,j,distance1[i][j]);
            }
        }
    }
}
//2Ϊ�ݳ�
void getData2(Graph* G){
    data();
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(distance2[i][j]!=100000) {
                G->setEdge(i, j, distance2[i][j]);
            }
        }
    }
}

