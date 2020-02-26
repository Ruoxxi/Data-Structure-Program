/*压缩文件*/
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include "CreateHuffman.h"

#define MAX 10000
using namespace std;

void openFileAndEncode(char inputFile[]);//打开文件并将内容读入input[]数组
void calWeight(char input[MAX], char outFile[]);//计算每个字符的权重
template<typename E> void encode(HuffNode<E>* forest, char* code, int deep, char outFile[]);//对每个字母编码
void build(char word[], int wgt[], int num, char outFile[]);//构建对应的huffmanTree
void EncodeOutputFile(char input[MAX], char name[]);//将压缩后的二进制码写入文件

/*全局变量*/
char codeList[100][100] = { 0 };//定义二维数组存储字母和对应的编码
int codeNum = 0;// i记录当前在数中查找到的叶子结点的数量

void openFileAndEncode(char inputFile[]) {
	char fileName[50] = "Decode//";
	strcat(fileName, inputFile);
	ifstream inFile(fileName);//打开目标文件

	if (!inFile.is_open())
	{
		cout << "文件不存在！" << endl;
		return;
	}

	char input[MAX] = { 0 };//将文件中的内容存储到数组
	int num = 0;
	string line;//存储每一行的内容

	while (getline(inFile, line)) {
		char temp[MAX];
		strcpy(temp, line.c_str());
		strcat(input, temp);
		strcat(input, "\n");//将换行符存入数组
	}
	inFile.close();//关闭文件

	cout << "请输入压缩后的文件名(xxx.bin)：";
	char outFile[30];
	cin >> outFile;
	char name[30] = "Encode//";
	strcat(name, outFile);

	calWeight(input, name);
	EncodeOutputFile(input, name);
}

void calWeight(char input[MAX], char outFile[]) {//计算每个字母的权重
	char word[100] = { NULL };//用于储存不同字母数组
	int wgt[100] = { 0 };//用于记录不同字母权重的数组

	int len = strlen(input);
	word[0] = input[0];
	int i, t;
	
	int num = 1;//记录不同字母的数量

	for (i = 0; i < len; i++) {
		int temp = 0;//用于判断当前字符是否是第一次出现
		for (t = 0; word[t] != NULL; t++) {
			if (input[i] == word[t]) {
				wgt[t]++;
				temp = 1;
				break;
			}
			else {
				temp = 0;
			}
		}
		if (temp == 0) {
			num++;
			word[t] = input[i];
			wgt[t]++;
		}
	}
	build(word ,wgt, num, outFile);
}

//build huffman tree
void build (char word[],int wgt[], int num, char outFile[]){
	int i;
	HuffTree<char>** forests = new HuffTree<char>*[num];
	for (i = 0; i < num; ++i) {
		//cout << word[i] << wgt[i] << endl;
		forests[i] = new HuffTree<char>(word[i], wgt[i]);
	}
	HuffTree<char>* forest = buildHuff(forests, num);
	
	ofstream out;
	out.open(outFile, ios::app|ios::binary);
	out << "每个字符对应的编码：" << endl;
	out.close();
	
	char codeSingle[100] = { 0 };

	encode(forest->root(), codeSingle, 0, outFile);	
};

//对消息编码
template<typename E> void encode(HuffNode<E>* forest, char* code, int deep, char outFile[]) {//deep指huffman树的深度
	if (forest->isLeaf() == true) {
		ofstream out;
		out.open(outFile, ios::app|ios::binary);

		if (!out.is_open()) {
			cout << "打开文件失败！" << endl;
			return;
		}
		
		codeList[codeNum][0] = ((LeafNode<E>*)forest)->val();
		strcat(codeList[codeNum], code);//codeList每一行的第一列记录字母，后面记录对应码值
		out << codeList[codeNum] << endl;//将对应码值输出到文件
		out.close();
		codeNum++;
	}
	if (forest->isLeaf() == false) {
		code[deep] = '0';//向左为0
		if (((IntlNode<E>*)forest)->left()) {
			encode(((IntlNode<E>*)forest)->left(), code, deep + 1, outFile);
		}
		code[deep] = '1';//向右为1
		if (((IntlNode<E>*)forest)->right()) {

			encode(((IntlNode<E>*)forest)->right(), code, deep + 1, outFile);
		}
	}
	code[deep] = 0;
}

//将压缩后的二进制码写入文件
void EncodeOutputFile(char input[MAX], char outFile[]) {
	ofstream out;
	out.open(outFile, ios::app|ios::binary);
	if (!out) {
		cout << "打开文件失败" << endl;
		return;
	}
	
	int i, t, p, q = 0;
	int len = strlen(input);
	out << "文件编码：" << endl;
	for (i = 0; i < len; i++) {//输出编码到目标文件
		for (t = 0; t < codeNum; t++) {
			if (input[i] == codeList[t][0]) {
				p = 1;//数组0号位存储字符，从1号位开始存储编码，因此从1号位开始输出
				while (codeList[t][p]) {
					out << codeList[t][p];
					p++;
				}
				break;
			}
		}
	}
	out.close();
};
