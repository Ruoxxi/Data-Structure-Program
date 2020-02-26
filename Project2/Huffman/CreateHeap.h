#include <assert.h>

template<typename E> void swap(E* array, int pos1, int pos2) {
	E temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

/*建立最小堆*/
template <typename E, typename Comp> class heap {
private:
	E* Heap;//指向堆数组
	int minsize;
	int n;//堆中的数的个数

	void siftdown(int pos) {//构建最小堆
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && Comp :: prior(Heap[rc], Heap[j])) {
				j = rc;//令j等于更小子树的值
			}
			if (Comp::prior(Heap[pos], Heap[j])) return;
			swap(Heap, pos, j); //交换当前值和最小结点的值
			pos = j;
		}
	}

public:
	heap(E* h, int num, int min) {//最小堆的初始化
		Heap = h;
		n = num;
		minsize = min;
		buildHeap();
	}

	int size ()const {//返回当前堆的大小
		return n;
	}
	bool isLeaf(int pos) const {//如果是叶子则返回true
		return (pos >= n / 2) && (pos < n);
	}

	int leftchild(int pos) const {//返回左孩子的位置
		return 2 * pos + 1;
	}
	int rightchild(int pos) const {//返回右孩子的位置
		return 2 * pos + 2;
	}
	int parent(int pos) const {//返回父结点的位置
		return (pos - 1) / 2;
	}
	void buildHeap() {//将数据排序
		int i;
		for (i = n / 2 - 1; i >= 0; i--) {
			siftdown(i);
		}
	}
	void insert(const E& it) {
		assert(n < minsize);
		int curr = n++;
		Heap[curr] = it;
		while ((curr != 0) && (Heap[curr] < Heap[parent(curr)])) {
			swap(Heap, curr, parent(curr));
			curr = parent(curr);
		}
	}
	E removefirst() {//去除最前面的数据
		assert(n > 0);
		swap(Heap, 0, --n);//第一个数据与最后一个交换
		if (n != 0)siftdown(0);
		return Heap[n];//返回删除的数据
	}
};
