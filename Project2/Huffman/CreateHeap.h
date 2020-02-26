#include <assert.h>

template<typename E> void swap(E* array, int pos1, int pos2) {
	E temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

/*������С��*/
template <typename E, typename Comp> class heap {
private:
	E* Heap;//ָ�������
	int minsize;
	int n;//���е����ĸ���

	void siftdown(int pos) {//������С��
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && Comp :: prior(Heap[rc], Heap[j])) {
				j = rc;//��j���ڸ�С������ֵ
			}
			if (Comp::prior(Heap[pos], Heap[j])) return;
			swap(Heap, pos, j); //������ǰֵ����С����ֵ
			pos = j;
		}
	}

public:
	heap(E* h, int num, int min) {//��С�ѵĳ�ʼ��
		Heap = h;
		n = num;
		minsize = min;
		buildHeap();
	}

	int size ()const {//���ص�ǰ�ѵĴ�С
		return n;
	}
	bool isLeaf(int pos) const {//�����Ҷ���򷵻�true
		return (pos >= n / 2) && (pos < n);
	}

	int leftchild(int pos) const {//�������ӵ�λ��
		return 2 * pos + 1;
	}
	int rightchild(int pos) const {//�����Һ��ӵ�λ��
		return 2 * pos + 2;
	}
	int parent(int pos) const {//���ظ�����λ��
		return (pos - 1) / 2;
	}
	void buildHeap() {//����������
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
	E removefirst() {//ȥ����ǰ�������
		assert(n > 0);
		swap(Heap, 0, --n);//��һ�����������һ������
		if (n != 0)siftdown(0);
		return Heap[n];//����ɾ��������
	}
};
