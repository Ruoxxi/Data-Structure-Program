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

void qsort(long *A, int i, long j, string option) {//i，j分别记录数组起始和结束的下标
	
	if (option == "2" || option == "4" || option == "6" || option == "7") {
		if (j - 1 <= 8) {//判断是否使用插入排序
			InsertSort(A, i, j);
		}
	}

	if (j <= i) return;//只有一个数或没有数时，返回
	long pivotindex;
	if (option == "1" || option == "4" || option == "5" || option == "7") {//使用第二种算轴值的方法
		pivotindex = findpivotPlus(A, i, j);
	}
	else {//使用第一种算轴值的方法
		pivotindex = findpivot(A, i, j);
	}

	swap(A, pivotindex, j);//将轴值放到最后
	int k = partition(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort(A, i, k - 1, option);
	qsort(A, k + 1, j, option);

}

//插入排序
void InsertSort(long *A, int r, long l) {
	int i, j;
	for (i = r + 1; i < l + 1; i++) {
		for (j = i; j > 1 && A[j] < A[j - 1]; j++) {
			swap(A, j, j - 1);
		}
	}
}

//第一种算轴值的方法
int findpivot(long *A, int i, long j) {
	return (i + j) / 2;
}

//第二种
int findpivotPlus(long *A, int i, long j) {//取第一个数、最后一个数和中间的数的中间值
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
	return l;//返回右边部分的第一个数的下标
}

void swap(long *A, int i, long j) {
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

