#include <iostream>
#include <time.h>
#include <stdlib.h>

#define MAX 10000

using namespace std;
void InsertSort(long *A, int r, long l);
int findpivot(long *A, int i, long j);
int findpivotPlus(long *A, int i, long j);
int partition(long *A, int l, long r, long& pivot);
void swap(long *A, int i, long j);

template<typename E> class Stack;
void useStack(long *A, int i, long j, string option);

void qsort(long *A, int i, long j, string option) {//i��j�ֱ��¼������ʼ�ͽ������±�
	
	if (option == "2" || option == "4" || option == "6" || option == "7") {
		if (j - 1 <= 8) {//�ж��Ƿ�ʹ�ò�������
			InsertSort(A, i, j);
		}
	}

	if (j <= i) return;//ֻ��һ������û����ʱ������
	long pivotindex;
	if (option == "1" || option == "4" || option == "5" || option == "7") {//ʹ�õڶ�������ֵ�ķ���
		pivotindex = findpivotPlus(A, i, j);
	}
	else {//ʹ�õ�һ������ֵ�ķ���
		pivotindex = findpivot(A, i, j);
	}

	swap(A, pivotindex, j);//����ֵ�ŵ����
	int k = partition(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort(A, i, k - 1, option);
	qsort(A, k + 1, j, option);

}

//��������
void InsertSort(long *A, int r, long l) {
	int i, j;
	for (i = r + 1; i < l + 1; i++) {
		for (j = i; j > 1 && A[j] < A[j - 1]; j++) {
			swap(A, j, j - 1);
		}
	}
}

//��һ������ֵ�ķ���
int findpivot(long *A, int i, long j) {
	return (i + j) / 2;
}

//�ڶ���
int findpivotPlus(long *A, int i, long j) {//ȡ��һ���������һ�������м�������м�ֵ
	if (A[i] > A[j] && A[j] > A[(i + j) / 2]){
		return j;
	}
	else if (A[j] > A[(i + j) / 2] && A[(i + j) / 2] > A[i]){
		return (i + j) / 2;
	}
	else {
		return i;
	}
}

int partition(long *A, int l, long r, long& pivot) {
	do {
		while (A[++l] > pivot);
		while ((l < r) && (pivot > A[--r]));
		swap(A, l, r);
	} while (l < r);
	return l;//�����ұ߲��ֵĵ�һ�������±�
}

void swap(long *A, int i, long j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

