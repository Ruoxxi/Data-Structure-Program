#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CreateHuffman.h"

using namespace std;
#define MAX 10000

/*ѹ���ļ�*/
void openFileAndEncode(char inputFile[]);//���ļ��������ݶ���input[]����

/*��ѹ���ļ�*/
void openFileAndDecode(char inputFile[]);//���ļ��������ݶ���input[]����

int main() {
	cout << "[1]ѹ���ļ�          [2]��ѹ���ļ�" << endl;
	cout << "���������֣�";
	string select;
	cin >> select;
	
	char inputFile[MAX];
	if (select == "1") {
		cout << "������Ҫѹ�����ļ���xxx.txt)��";
		cin >> inputFile;
		openFileAndEncode(inputFile);
	}
	else if (select == "2") {
		cout << "������Ҫ��ѹ�����ļ���xxx.bin)��";
		cin >> inputFile;
		openFileAndDecode(inputFile);
	}
	else {
		cout << "��ָ����ڣ�" << endl;
	}
	system("pause");
}



