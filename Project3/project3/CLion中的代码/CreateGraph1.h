//生成图
#include <iostream>
#include <assert.h>
#include "Graph1.h"

#define UNVISITED 0
#define www 1/0.0L
class Graphm : public Graph {
private:
    int numVertex,numEdge;
    double** matrix;
    int* mark;
public:
    Graphm(int numVert)
    { Init(numVert); }

    ~Graphm(){
        delete [] mark;
        for(int i=0;i<numVertex;i++)
            delete [] matrix[i];
        delete [] matrix;
    }

    void Init(int n){
        int i;
        numVertex=n;
        numEdge=0;
        mark= new int[n];
        for(i=0;i<numVertex;i++)
            mark[i]=UNVISITED;
        matrix= (double **) new int *[numVertex];
        for(i=0;i<numVertex;i++)
            matrix[i]=new double[numVertex];
        for(i=0;i<numVertex;i++)
            for(int j=0;j<numVertex;j++)
                matrix[i][j]=www;
    }

    int n(){ return numVertex;}
    int e(){ return numEdge;}

    int first(int v){
        for(int i=0;i<numVertex;i++)
            if(matrix[v][i]!=www) return i;
        return numVertex;
    }

    int next(int v, int w){
        for(int i=w+1;i<numVertex;i++)
            if(matrix[v][i]!=www)
                return i;
        return numVertex;
    }

    void setEdge(int v1,int v2,double wt){
        assert(wt>=0);
        if(matrix[v1][v2]==www) numEdge++;
        matrix[v1][v2]=wt;
    }

    void delEdge(int v1,int v2){
        if(matrix[v1][v2]!=www) numEdge--;
        matrix[v1][v2]=www;
    }

    bool isEdge(int i,int j)
    {return matrix[i][j]!=www;}

    double weight(int v1,int v2){return matrix[v1][v2];}
    int getMark(int v){return mark[v];}
    void setMark(int v,int val){mark[v]=val;}
};
