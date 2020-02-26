/*ѹ���ļ�*/
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include "CreateHuffman.h"

#define MAX 10000
using namespace std;

void openFileAndEncode(char inputFile[]);//���ļ��������ݶ���input[]����
void calWeight(char input[MAX], char outFile[]);//����ÿ���ַ���Ȩ��
template<typename E> void encode(HuffNode<E>* forest, char* code, int deep, char outFile[]);//��ÿ����ĸ����
void build(char word[], int wgt[], int num, char outFile[]);//������Ӧ��huffmanTree
void EncodeOutputFile(char input[MAX], char name[]);//��ѹ����Ķ�������д���ļ�

/*ȫ�ֱ���*/
char codeList[100][100] = { 0 };//�����ά����洢��ĸ�Ͷ�Ӧ�ı���
int codeNum = 0;// i��¼��ǰ�����в��ҵ���Ҷ�ӽ�������

void openFileAndEncode(char inputFile[]) {
	char fileName[50] = "Decode//";
	strcat(fileName, inputFile);
	ifstream inFile(fileName);//��Ŀ���ļ�

	if (!inFile.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		return;
	}

	char input[MAX] = { 0 };//���ļ��е����ݴ洢������
	int num = 0;
	string line;//�洢ÿһ�е�����

	while (getline(inFile, line)) {
		char temp[MAX];
		strcpy(temp, line.c_str());
		strcat(input, temp);
		strcat(input, "\n");//�����з���������
	}
	inFile.close();//�ر��ļ�

	cout << "������ѹ������ļ���(xxx.bin)��";
	char outFile[30];
	cin >> outFile;
	char name[30] = "Encode//";
	strcat(name, outFile);

	calWeight(input, name);
	EncodeOutputFile(input, name);
}

void calWeight(char input[MAX], char outFile[]) {//����ÿ����ĸ��Ȩ��
	char word[100] = { NULL };//���ڴ��治ͬ��ĸ����
	int wgt[100] = { 0 };//���ڼ�¼��ͬ��ĸȨ�ص�����

	int len = strlen(input);
	word[0] = input[0];
	int i, t;
	
	int num = 1;//��¼��ͬ��ĸ������

	for (i = 0; i < len; i++) {
		int temp = 0;//�����жϵ�ǰ�ַ��Ƿ��ǵ�һ�γ���
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
	out << "ÿ���ַ���Ӧ�ı��룺" << endl;
	out.close();
	
	char codeSingle[100] = { 0 };

	encode(forest->root(), codeSingle, 0, outFile);	
};

//����Ϣ����
template<typename E> void encode(HuffNode<E>* forest, char* code, int deep, char outFile[]) {//deepָhuffman�������
	if (forest->isLeaf() == true) {
		ofstream out;
		out.open(outFile, ios::app|ios::binary);

		if (!out.is_open()) {
			cout << "���ļ�ʧ�ܣ�" << endl;
			return;
		}
		
		codeList[codeNum][0] = ((LeafNode<E>*)forest)->val();
		strcat(codeList[codeNum], code);//codeListÿһ�еĵ�һ�м�¼��ĸ�������¼��Ӧ��ֵ
		out << codeList[codeNum] << endl;//����Ӧ��ֵ������ļ�
		out.close();
		codeNum++;
	}
	if (forest->isLeaf() == false) {
		code[deep] = '0';//����Ϊ0
		if (((IntlNode<E>*)forest)->left()) {
			encode(((IntlNode<E>*)forest)->left(), code, deep + 1, outFile);
		}
		code[deep] = '1';//����Ϊ1
		if (((IntlNode<E>*)forest)->right()) {

			encode(((IntlNode<E>*)forest)->right(), code, deep + 1, outFile);
		}
	}
	code[deep] = 0;
}

//��ѹ����Ķ�������д���ļ�
void EncodeOutputFile(char input[MAX], char outFile[]) {
	ofstream out;
	out.open(outFile, ios::app|ios::binary);
	if (!out) {
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	
	int i, t, p, q = 0;
	int len = strlen(input);
	out << "�ļ����룺" << endl;
	for (i = 0; i < len; i++) {//������뵽Ŀ���ļ�
		for (t = 0; t < codeNum; t++) {
			if (input[i] == codeList[t][0]) {
				p = 1;//����0��λ�洢�ַ�����1��λ��ʼ�洢���룬��˴�1��λ��ʼ���
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
