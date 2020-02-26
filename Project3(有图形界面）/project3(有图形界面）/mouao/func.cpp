//#include<iostream>
#include <QMessageBox>
#include"CreateGraph1.h"
#define www 1/0.0L
using namespace std;
void getData1(Graph* G);
void getData2(Graph* G);
void Dijkstra(Graph *G, double *D, int *P,int s);
string findname(int a);
int func(int in, int out, int way) {
    double D[25];
    int P[25];
//    cout << "程序开始：\n" << endl;
//    cout << "请输入起点：0.西园十舍 1.青春广场 2.2号运动场 3.3号运动场 4.一教A 5.一教B 6.一教C 7.一教D 8.综B 9.综C 10.一基楼A\n" << endl;
//    cout << "11.一基楼B 12.法学院 13.艺术学院 14.二基楼 15.游泳池 16.文科楼 17.图书馆 18.体育馆 19.建环楼 20.工训中心\n" << endl;
//    cout << "21.保卫处 22.体育学院 23.三餐 24.华联\n" << endl;
//    cin >> in;
//    cout << "请输入终点：0.西园十舍 1.青春广场 2.2号运动场 3.3号运动场 4.一教A 5.一教B 6.一教C 7.一教D 8.综B 9.综C 10.一基楼A\n" << endl;
//    cout << "11.一基楼B 12.法学院 13.艺术学院 14.二基楼 15.游泳池 16.文科楼 17.图书馆 18.体育馆 19.建环楼 20.工训中心\n" << endl;
//    cout << "21.保卫处 22.体育学院 23.三餐 24.华联\n" << endl;
//    cin >> out;
//    cout << "请选择出行方式：1.步行 2.驾车" << endl;
//    cin >> way;
    Graphm G1(25);//生成图1，步行
    getData1(&G1);//构建图的边
    Graphm G2(25);//生成图2，驾车
    getData2(&G2);//构建图的边
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
//        cout<<"输入错误！" <<endl;
        QMessageBox::information(NULL, "Error", "illeagal input",QMessageBox::Yes|QMessageBox::No);
        return 0;
    }
    if (D[out] >= 100000) {
//        cout << "此路不通！" << endl;
        QMessageBox::information(NULL, "!", "no path", QMessageBox::Yes|QMessageBox::No);
        return 0;
    }

    string ans;
//    cout << "最短路径是：" << D[out] <<"m"<< endl;
    ans += "最短路径是： " + to_string(D[out]) + "m\n";
    ans += "路径： ";
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
        ans += findname(a[i]);
        ans += " -> ";
        //cout<<a[i]<<"->";
    }
    ans += findname(a[0]);

    QMessageBox::information(NULL, "Path", ans.data(), QMessageBox::Ok);
    return 0;
}


