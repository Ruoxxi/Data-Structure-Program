#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;
#define MAX 1000
void main() {
	float info[MAX][4];
	string name[MAX];
	cout << "请输入学生的姓名 语文 数学 英语成绩(输入“q”结束):\n" << endl;
	
	int i;
	for (i = 0; ; i++) {
		cin >> name[i];
	/*	getchar();*/
		if (name[i]=="q") {
			break;
		}
		cin >> info[i][0] >> info[i][1] >> info[i][2];
		info[i][3] = info[i][1] + info[i][2] + info[i][0];
	}
	int num = i;
	int t,p;
	for (t = 0; t < num; t++) {
		for (p = 0; p < num - t - 1; p++) {
			if (info[p][3] < info[p + 1][3]) {
				string temp = name[p];
				name[p] = name[p + 1];
				name[p + 1] = temp;
				float b[4];//中间数组
				memcpy(b, info[p], sizeof(b));
				memcpy(info[p], info[p + 1], sizeof(b));
				memcpy(info[p + 1], b, sizeof(b));
			}
		}
	}
	ofstream file("C:\student.txt");
	if (!file) {
		cout << "Failed to create file...\n";
		//exit(0);
	}
	file << "姓名" << "\t" << "语文" << "\t" << "数学" << "\t" << "英语" << "\t" << "总分"<<endl;
	int j;
	for (i = 0; i < num; i++) {
		file << name[i] << "\t" << info[i][0]<<"\t"<<info[i][1]<<"\t"<<info[i][2]<<"\t"<<info[i][3]  << endl;
	}file.close();
	string str;
	ifstream ifs("C:\student.txt");
	for (; ifs.good();) {
		getline(ifs, str);
		cout << str << endl;
	}
	ifs.close();
	system("pause");
}