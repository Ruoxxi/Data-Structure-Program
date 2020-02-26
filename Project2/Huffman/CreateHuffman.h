#include <iostream>

#include <fstream>
#include "CreateHeap.h"
#include <vector>
using std::vector;


using namespace std;

/*huffman������ʵ��*/
template <typename E> class HuffNode {
public:
	virtual ~HuffNode(){}
	virtual int weight() = 0;//Ȩ��
	virtual bool isLeaf() = 0;//�ж���Ҷ��㻹���ڲ����
};

template <typename E> class LeafNode : public HuffNode<E> {//Ҷ�ӽ��
private:
	E it;//Value
	int wgt;//Weight
public:
	LeafNode(const E& val, int freq) {
		it = val; 
		wgt = freq;
	}
	int weight() {
		return wgt;
	}
	E val() {
		return it;
	}
	bool isLeaf() {
		return true;
	}
};

template <typename E> class IntlNode : public HuffNode<E> {//�ڲ����
private:
	HuffNode<E>* lc;//Left child
	HuffNode<E>* rc;//Right child
	int wgt;//Subtree weight
public:
	IntlNode(HuffNode<E>*l, HuffNode<E>*r) {
		wgt = l->weight() + r->weight();//����Ȩ��Ϊ������Ȩ��+������Ȩ��
		lc = l;
		rc = r;
	}
	int weight() { 
		return wgt;
	}
	bool isLeaf() {
		return false;
	}

	HuffNode<E>* left() const {
		return lc;
	}
	void setLeft(HuffNode<E>* b) {
		lc = (HuffNode<E>*)b;
	}
	HuffNode<E>* right() const {
		return rc;
	}
	void setRight(HuffNode<E>* b) {
		rc = (HuffNode<E>*)b;
	}
};


/*Huffman������˵��*/  
template <typename E> class HuffTree {
private:
	HuffNode<E>* Root;
public:
	HuffTree(E& val, int freq) {//����Ҷ�ӽ��
		Root = new LeafNode<E>(val, freq);
	}
	HuffTree(HuffTree<E>* l, HuffTree<E>*r) {//�����ڲ����
		Root = new IntlNode<E>(l->root(), r -> root());
	}

	~HuffTree(){}

	HuffNode<E>* root() {																	
		return Root;
	}
	int weight() {
		return Root->weight();
	}
};


/*Huffman�����캯����ʵ��*/
template<typename E> class minTreeComp {
public:
	static bool prior(HuffTree<E>* a, HuffTree<E>* b) {
		return b->weight() >= a->weight();
	}
};

template <typename E> HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, minTreeComp<E>>* forest = new heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);//��ʼ���µ���С��forest

	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
	while (forest->size() > 1) {
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();//ȥ����ǰ�����������
		temp3 = new HuffTree<E>(temp1, temp2);//�����µĸ����
		forest->insert(temp3);//���µ����������Ա�
		delete temp1;
		delete temp2;	
	}
	return temp3;
}

//template<typename E> void traverse(HuffNode<E>* forest, char outFile[]) {//�������
//	ofstream out;
//	out.open(outFile, ios::app);
//	if (forest->isLeaf() == true) {
//		if (!out) {
//			cout << "�����ļ�ʧ��" << endl;
//			return;
//		}
//		if (((LeafNode<E>*)forest)->val() == "\n") {
//			out<< "���з� : " << forest->weight() << endl;
//		}
//		else {
//			out << ((LeafNode<E>*)forest)->val() << " : " << forest->weight() << endl;
//		}
//	}
//	else {
//		out << forest->weight() << endl;
//		traverse(((IntlNode<E>*)forest)->left(), outFile);
//
//		traverse(((IntlNode<E>*)forest)->right(), outFile);
//	}
//	out.close();
//}
