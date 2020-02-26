#include <iostream>

#include <string>
#include <stdlib.h>



#define MAX 10000

using namespace std;
void InsertSort(long *A, int r, long l);
int findpivot(long *A, int i, long j);
int findpivotPlus(long *A, int i, long j);
int partition(long *A, int l, long r, long& pivot);
void swap(long *A, int i, long j);

/*用堆栈存储*/

template<typename E>
class AStack {
private :
	int maxsize = 100;
	int top = 0;
	E *listArray = new E[maxsize];

public:
		void clear() {
			top = 0;
		}
		void push(E it) {
			listArray[top++] = it;
		}
		E pop() {
			return listArray[--top];
		}
		const E& topValue() const {
			if (top != 0) {
				return listArray[top - 1];
			}
			
		}
		int length() const {
			return top;
		}
};


void useStack(long*A, int i, long j, string option) {
	AStack<int> s;
	int pivotindex;

	s.push(j);
	s.push(i);
	while (s.length()>0) {
		i = s.topValue();
		s.pop();
		j = s.topValue();
		s.pop();
		if (option == "6" || option == "7") {
			if (j - 1 <= 8) {//判断是否使用插入排序
				InsertSort(A, i, j);
				continue;
			}
		}
		if (j <= i) continue;//只有一个数或没有数时

		if (option == "5" || option == "7") {//使用第二种算轴值的方法
			pivotindex = findpivotPlus(A, i, j);
		}
		else {//使用第一种算轴值的方法
			pivotindex = findpivot(A, i, j);
		}
	
		swap(A, pivotindex, j);//将轴值放到最后
		int k = partition(A, i - 1, j, A[j]);
		swap(A, k, j);

		if ((k - i) > (j - k)) {//先压入长的一部分
			s.push(k - 1);
			s.push(i);
			s.push(j);
			s.push(k + 1);
		}
		else {
			s.push(j);
			s.push(k + 1);
			s.push(k - 1);
			s.push(i);
		}
	}
	s.clear();
}