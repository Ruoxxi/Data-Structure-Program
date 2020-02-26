/*��ѹ���ļ�*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "CreateHuffman.h"

using namespace std;
#define MAX 10000

void openFileAndDecode(char inputFile[]);//���ļ������ļ���ͷ�ĸ��ַ�����洢����ά����
void findVal(char input[MAX]);//��huffman�����ҵ������Ӧ���ַ�
void DecodeOutputFile(char decode[]);//����ѹ����ַ���������ļ�

/*ȫ�ֱ���*/
char wordList[100];//�洢�����ַ�
string codeList[100];//�洢�����ַ���Ӧ�ı���

/*���ļ���ͷ�ĸ��ַ��Ͷ�Ӧ����洢����ά����*/
void openFileAndDecode(char inputFile[]) {
	char fileName[50] = "Encode//";
	strcat(fileName, inputFile);

	ifstream inFile(fileName);//��Ŀ���ļ�
	if (!inFile.is_open())
	{
		cout << "���ļ������ڣ�" << endl;
		return;
	}

	int num = 0;
	string line;//ɨ��ÿһ�е�����
	getline(inFile, line);//��Ϊ�ļ���ͷ��һ���ǲ���ص��ַ��������Դӵڶ��п�ʼ��
	int i = 0;
	while (getline(inFile, line)) {
		string::size_type code = line.find("�ļ�����");
		if (code != string::npos) {//��ȡ���ļ����롱֮ǰ������
			break;
		}
		if (line.size() != 0) {//���ַ��Ͷ�Ӧ��������ά����
			wordList[i] = line[0];
			codeList[i] = line.substr(1,98);//�ӽǱ�Ϊ1��λ�ø���
		}
		else {//������Ϊ���У�˵���洢����'\n'����������У���һ��Ϊ�س��ַ���Ӧ�ı���
			wordList[i] = '\n';
			getline(inFile, line);
			codeList[i] = line;
		}
		i++;
	}
	inFile.close();//�ر��ļ�
	findVal(fileName);
}

/*���Ҷ�Ӧ��ֵ������ѹ����ַ���д������*/
void findVal(char fileName[MAX]) {
	ifstream inFile(fileName);//��Ŀ���ļ�
	if (!inFile.is_open())
	{
		cout << "���ļ������ڣ�" << endl;
		return;
	}

	string line;//ɨ��ÿһ�е�����
	while (getline(inFile, line)) {//���ļ�ָ���Ƶ����ļ����룺����һ��
		string::size_type code = line.find("�ļ�����");
		if (code == string::npos) {
			continue;
		}
		else {
			break;
		}
	}

	char code[MAX] = { 0 };//�洢��ֵ
	int i = 0;
	while (!inFile.eof()) {
		inFile >> code[i];
		i++;
	}

	char decode[MAX] = { 0 };//�洢�������ַ�
	int m = 0;//decode[]�ĽǱ�
	int t;
	string temp;//��ʱ�ַ��������ڴ�code[]�ж�ȡ����
	temp = code[0];
	int ifFind = 0;//���ҵ���Ӧ�ַ���Ϊ1
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
		if (ifFind == 0) {//��û���ҵ��������ӳ�һ���ַ�
			temp += code[i];
		}
		else {
			ifFind = 0;
			temp = code[i];
		}		
	}
	inFile.close();//�ر��ļ�
	DecodeOutputFile(decode);
}

/*����ѹ����ַ���������ļ�*/
void DecodeOutputFile(char decode[]) {
	cout << "�������ѹ������ļ���(xxx.txt)��";
	char outFile[30];
	cin >> outFile;
	char fileName[30] = "Decode//";
	strcat(fileName, outFile);
	ofstream out(fileName);
	if (!out.is_open()) {
		cout << "�����ļ�ʧ�ܣ�" << endl;
		return;
	}

	int i;
	int len = strlen(decode);
	for (i = 0; i < len; i++) {
		out << decode[i];
	}
}
	