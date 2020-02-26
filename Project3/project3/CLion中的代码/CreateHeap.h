#include<assert.h>
//交换
template<typename E> void swap(E* array, int pos1, int pos2) {
    E temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}
//构建最小堆
template <typename E,typename Comp> class heap{
private:
    E* Heap;
    int minsize;
    int n;

    void siftdown(int pos){
        while(!isLeaf(pos)){
            int j=leftchild(pos);
            int rc=rightchild(pos);
            if((rc<n)&&(Comp::prior(Heap[rc],Heap[j])))
                j=rc;
            if(Comp::prior(Heap[pos],Heap[j])) return;
            swap(Heap,pos,j);
            pos=j;
        }
    }

public:
    heap(E* h,int num,int min){
        Heap=h;
        n=num;
        minsize=min;
        buildHeap();
    }
    int size() const {return n;}
    int isLeaf(int pos) const {
        return (pos>=n/2)&&(pos<n);
    }
    int leftchild(int pos) const {
        return 2*pos+1;
    }
    int rightchild(int pos) const {
        return 2*pos+2;
    }
    int parent(int pos) const {
        return (pos-1)/2;
    }
    void buildHeap(){
        for(int i=n/2-1;i>=0;i--){
            siftdown(i);
        }
    }
    //insert "it" into the Heap
    void insert(const E& it){
        assert(n>=0);
        int curr=n++;
        Heap[curr]=it;
        while((curr!=0)&&(Comp::prior(Heap[curr],Heap[parent(curr)]))){
            swap(Heap,curr,parent(curr));
            curr=parent(curr);
        }
    }
    //remove first value
    E removefirst(){
        assert(n>=0);
        swap(Heap,0,--n);
        if(n!=0) siftdown(0);
        return Heap[n];
    }
    //remove and return element at specified position
    E remove(int pos){
        assert((pos>=0)&&(pos<n));
        if(pos==(n-1)) n--;
        else{
            swap(Heap,pos,--n);
            while((pos!=0)&&(Comp::prior(Heap[pos],Heap[parent(pos)]))){
                swap(Heap,pos,parent(pos));
                pos=parent(pos);
            }
            if(n!=0) siftdown(pos);
        }
        return Heap[n];
    }
};
