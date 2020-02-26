/*解压缩文件*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CreateHuffman.h"

using namespace std;
#define MAX 10000

void openFileAndDecode(char inputFile[]);//打开文件并将文件开头的各字符编码存储到二维数组
void findVal(char input[MAX]);//在huffman树中找到编码对应的字符
void DecodeOutputFile(char decode[]);//将解压后的字符串输出到文件

/*全局变量*/
char wordList[100];//存储各个字符
string codeList[100];//存储各个字符对应的编码

/*将文件开头的各字符和对应编码存储到二维数组*/
void openFileAndDecode(char inputFile[]) {
	char fileName[50] = "Encode//";
	strcat(fileName, inputFile);

	ifstream inFile(fileName);//打开目标文件
	if (!inFile.is_open())
	{
		cout << "该文件不存在！" << endl;
		return;
	}

	int num = 0;
	string line;//扫描每一行的内容
	getline(inFile, line);//因为文件开头第一行是不相关的字符串，所以从第二行开始读
	int i = 0;
	while (getline(inFile, line)) {
		string::size_type code = line.find("文件编码");
		if (code != string::npos) {//读取“文件编码”之前的内容
			break;
		}
		if (line.size() != 0) {//将字符和对应编码存入二维数组
			wordList[i] = line[0];
			codeList[i] = line.substr(1,98);//从角标为1的位置复制
		}
		else {//若该行为空行，说明存储的是'\n'，则读入两行，下一行为回车字符对应的编码
			wordList[i] = '\n';
			getline(inFile, line);
			codeList[i] = line;
		}
		i++;
	}
	inFile.close();//关闭文件
	findVal(fileName);
}

/*查找对应码值并将解压后的字符串写入数组*/
void findVal(char fileName[MAX]) {
	ifstream inFile(fileName);//打开目标文件
	if (!inFile.is_open())
	{
		cout << "该文件不存在！" << endl;
		return;
	}

	string line;//扫描每一行的内容
	while (getline(inFile, line)) {//将文件指针移到“文件编码：”下一行
		string::size_type code = line.find("文件编码");
		if (code == string::npos) {
			continue;
		}
		else {
			break;
		}
	}

	char code[MAX] = { 0 };//存储码值
	int i = 0;
	while (!inFile.eof()) {
		inFile >> code[i];
		i++;
	}

	char decode[MAX] = { 0 };//存储解码后的字符
	int m = 0;//decode[]的角标
	int t;
	string temp;//临时字符串，用于从code[]中读取编码
	temp = code[0];
	int ifFind = 0;//若找到对应字符则为1
	int len = strlen(code);
	for (i = 1; i < len; i++) {
		for (t = 0; !codeList[t].empty(); t++) {
			if (temp.compare(codeList[t])==0) {
				decode[m] = wordList[t];
				m++;
				ifFind = 1;
				break;
			}
		}
		if (ifFind == 0) {//若没有找到则往后延长一个字符
			temp += code[i];
		}
		else {
			ifFind = 0;
			temp = code[i];
		}		
	}
	inFile.close();//关闭文件
	DecodeOutputFile(decode);
}

/*将解压后的字符串输出到文件*/
void DecodeOutputFile(char decode[]) {
	cout << "请输入解压缩后的文件名(xxx.txt)：";
	char outFile[30];
	cin >> outFile;
	char fileName[30] = "Decode//";
	strcat(fileName, outFile);
	ofstream out(fileName);
	if (!out.is_open()) {
		cout << "创建文件失败！" << endl;
		return;
	}

	int i;
	int len = strlen(decode);
	for (i = 0; i < len; i++) {
		out << decode[i];
	}
}
	