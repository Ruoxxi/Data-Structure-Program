#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#define MAX 1000000
using namespace std;

void qsort(long *A, int i, long j, string option);
void useStack(long *A, int i, long j, string option);
void menu() {
	cout << "[1] A�Ż�" << endl;
	cout << "[2] B�Ż�" << endl;
	cout << "[3] C�Ż�" << endl;
	cout << "[4] A�Ż� + B�Ż�" << endl;
	cout << "[5] A�Ż� + C�Ż�" << endl;
	cout << "[6] B�Ż� + C�Ż�" << endl;
	cout << "[7] A�Ż� + B�Ż� + C�Ż�" << endl;
	cout << "[8] ���Ż�" << endl;
	cout << "[0] �˳�����" << endl;
}


void createRandom(long N, string option) {//���������
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
	long start, end;//�ֱ��¼��ʼʱ��ͽ���ʱ��

	start = clock();
	createRandom(10, option);
	end = clock();
	cout << "N = 10ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;

	start = clock();
	createRandom(100, option);
	end = clock();
	cout << "N = 100ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;

	start = clock();
	createRandom(1000, option);
	end = clock();
	cout << "N = 1000ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;

	start = clock();
	createRandom(10000, option);
	end = clock();
	cout << "N = 10000ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;

	start = clock();
	createRandom(100000, option);
	end = clock();
	cout << "N = 100000ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;

	start = clock();
	createRandom(1000000, option);
	end = clock();
	cout << "N = 1000000ʱ�����Ż�������ʱ��" << end - start << "ms" << endl;
}


void main() {
	string option = "-1";//�û���ѡ��
	while (option != "0") {
		menu();
		cin >> option;
		if (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7" && option != "8" && option != "0") {
			cout << "����������������룡" << endl;
		}
		else if (option == "0") {
			cout << "�˳��ɹ���" << endl;
		}
		else {
			N(option);
		}
	}
	system("pause");
}
