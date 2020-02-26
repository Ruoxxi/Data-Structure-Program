#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CreateHuffman.h"

using namespace std;
#define MAX 10000

/*压缩文件*/
void openFileAndEncode(char inputFile[]);//打开文件并将内容读入input[]数组

/*解压缩文件*/
void openFileAndDecode(char inputFile[]);//打开文件并将内容读入input[]数组

int main() {
	cout << "[1]压缩文件          [2]解压缩文件" << endl;
	cout << "请输入数字：";
	string select;
	cin >> select;
	
	char inputFile[MAX];
	if (select == "1") {
		cout << "请输入要压缩的文件（xxx.txt)：";
		cin >> inputFile;
		openFileAndEncode(inputFile);
	}
	else if (select == "2") {
		cout << "请输入要解压缩的文件（xxx.bin)：";
		cin >> inputFile;
		openFileAndDecode(inputFile);
	}
	else {
		cout << "该指令不存在！" << endl;
	}
	system("pause");
}



