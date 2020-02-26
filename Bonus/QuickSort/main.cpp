#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#define MAX 1000000
using namespace std;

void qsort(long *A, int i, long j, string option);
void useStack(long *A, int i, long j, string option);
void menu() {
	cout << "[1] A优化" << endl;
	cout << "[2] B优化" << endl;
	cout << "[3] C优化" << endl;
	cout << "[4] A优化 + B优化" << endl;
	cout << "[5] A优化 + C优化" << endl;
	cout << "[6] B优化 + C优化" << endl;
	cout << "[7] A优化 + B优化 + C优化" << endl;
	cout << "[8] 不优化" << endl;
	cout << "[0] 退出程序" << endl;
}


void createRandom(long N, string option) {//生成随机数
	srand(time(NULL));
	long A[1000000];
	long i;
	for (i = 0; i < N; i++) {
		A[i] = rand() % N +1 ;
	}
	if (option == "3" || option == "5" || option == "6" || option == "7") {
		useStack(A, 0, N-1, option);
	}
	else {
		qsort(A, 0, N-1, option);
	}
}


void N(string option) {
	long start, end;//分别记录开始时间和结束时间

	start = clock();
	createRandom(10, option);
	end = clock();
	cout << "N = 10时，该优化方案耗时：" << end - start << "ms" << endl;

	start = clock();
	createRandom(100, option);
	end = clock();
	cout << "N = 100时，该优化方案耗时：" << end - start << "ms" << endl;

	start = clock();
	createRandom(1000, option);
	end = clock();
	cout << "N = 1000时，该优化方案耗时：" << end - start << "ms" << endl;

	start = clock();
	createRandom(10000, option);
	end = clock();
	cout << "N = 10000时，该优化方案耗时：" << end - start << "ms" << endl;

	start = clock();
	createRandom(100000, option);
	end = clock();
	cout << "N = 100000时，该优化方案耗时：" << end - start << "ms" << endl;

	start = clock();
	createRandom(1000000, option);
	end = clock();
	cout << "N = 1000000时，该优化方案耗时：" << end - start << "ms" << endl;
}


void main() {
	string option = "-1";//用户的选择
	while (option != "0") {
		menu();
		cin >> option;
		if (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7" && option != "8" && option != "0") {
			cout << "输入错误！请重新输入！" << endl;
		}
		else if (option == "0") {
			cout << "退出成功！" << endl;
		}
		else {
			N(option);
		}
	}
	system("pause");
}
