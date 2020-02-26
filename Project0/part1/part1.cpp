#include <iostream>

using namespace std;

template <class T>
T* find(T a, T b, T c) {
	T output[2];
	T max = a, min = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	output[0] = min;
	output[1] = max;
	return output;
}

//void main( ){
//	char *p = find('a', 'b', 'c');
//	cout << *p << " " << *p++ << endl;
//	system("pause");
//}
