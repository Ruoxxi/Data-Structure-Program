#include<iostream>
#include"CreateGraph1.h"
#define www 1/0.0L
using namespace std;
void getData1(Graph* G);
void getData2(Graph* G);
void Dijkstra(Graph *G, double *D, int *P,int s);
void findname(int a);
int main() {
	int in, out;
	int way;
	double D[25];
	int P[25];
    cout << "����ʼ��\n" << endl;
	cout << "��������㣺0.��԰ʮ�� 1.�ഺ�㳡 2.2���˶��� 3.3���˶��� 4.һ��A 5.һ��B 6.һ��C 7.һ��D 8.��B 9.��C 10.һ��¥A\n" << endl;
	cout << "11.һ��¥B 12.��ѧԺ 13.����ѧԺ 14.����¥ 15.��Ӿ�� 16.�Ŀ�¥ 17.ͼ��� 18.������ 19.����¥ 20.��ѵ����\n" << endl;
	cout << "21.������ 22.����ѧԺ 23.���� 24.����\n" << endl;
	cin >> in;
	cout << "�������յ㣺0.��԰ʮ�� 1.�ഺ�㳡 2.2���˶��� 3.3���˶��� 4.һ��A 5.һ��B 6.һ��C 7.һ��D 8.��B 9.��C 10.һ��¥A\n" << endl;
	cout << "11.һ��¥B 12.��ѧԺ 13.����ѧԺ 14.����¥ 15.��Ӿ�� 16.�Ŀ�¥ 17.ͼ��� 18.������ 19.����¥ 20.��ѵ����\n" << endl;
	cout << "21.������ 22.����ѧԺ 23.���� 24.����\n" << endl;
	cin >> out;
	cout << "��ѡ����з�ʽ��1.���� 2.�ݳ�" << endl;
	cin >> way;
	Graphm G1(25);//����ͼ1������ 
	getData1(&G1);//����ͼ�ı� 
	Graphm G2(25);//����ͼ2���ݳ� 
	getData2(&G2);//����ͼ�ı� 
	for(int i=0;i<25;i++){
	    P[i]=i;
	}
	if (way == 1) {
		for (int i = 0; i < 25; i++) {
			D[i] = www;
		}
		D[in]=0;
        Dijkstra(&G1, D, P,in);
	}
	else if (way == 2) {
		for (int i = 0; i < 25; i++) {
			D[i] = www;
		}
		D[in]=0;
        Dijkstra(&G2, D, P, in);
	}
	else {
		cout<<"�������" <<endl; 
		return 0;
	}
	if (D[out] >= 100000) {
		cout << "��·��ͨ��" << endl;
		return 0;
	}
	cout << "���·���ǣ�" << D[out] <<"m"<< endl;
	cout << "·����";
	int a[25];
	int m=0;
	while(1){
        /*if(P[out]!=out){
            printf("%d<-%d ",out,P[out]);
            out=P[out];
            continue;
        }*/
        if(P[out]!=out){
            a[m]=out;
            out=P[out];
            m++;
            continue;
        }
        a[m]=in;
        break;
	}
    for(int i=m;i>0;i--){
        findname(a[i]);
        cout<<"->";
        //cout<<a[i]<<"->";
    }
    findname(a[0]);
}


