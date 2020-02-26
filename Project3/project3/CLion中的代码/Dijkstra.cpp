#include"CreateHeap.h"
#include"CreateGraph1.h"
#define VISITED 1
#define INFINITY 1/0.0L
class DijkElem{
public:
    int vertex;
    double distance;
    DijkElem(){vertex=-1;distance=-1;}
    DijkElem(int v,int d){vertex=v;distance=d;}
    //double getDistance(){return this->distance;}
};
class DDComp{
public:
    static bool prior(DijkElem v1,DijkElem v2){
        return v2.distance>=v1.distance;
    }
};
//Dijkstra找最短路径
void Dijkstra(Graph* G,double *D,int* P,int s){
    int i,v,w;
    DijkElem temp;
    
    DijkElem E[G->e()];
    temp.distance=0;
    temp.vertex=s;
    E[0]=temp;
    heap <DijkElem,DDComp> H(E,1,G->e());
    for(i=0;i<G->n();i++){
        do{
            if(H.size()==0) return;
            temp = H.removefirst();
            v=temp.vertex;
        }while(G->getMark(v)==VISITED);
        G->setMark(v,VISITED);
        if(D[v]==INFINITY) return;
        for(w=G->first(v);w<G->n();w=G->next(v,w)) {
            if (D[w] > (D[v] + G->weight(v, w))) {
                D[w] = D[v] + G->weight(v, w);
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);
                P[w] = v;
            }
        }
    }
}

