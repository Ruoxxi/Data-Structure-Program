#include <iostream>

#include <fstream>
#include "CreateHeap.h"
#include <vector>
using std::vector;


using namespace std;

/*huffman树结点的实现*/
template <typename E> class HuffNode {
public:
	virtual ~HuffNode(){}
	virtual int weight() = 0;//权重
	virtual bool isLeaf() = 0;//判断是叶结点还是内部结点
};

template <typename E> class LeafNode : public HuffNode<E> {//叶子结点
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

template <typename E> class IntlNode : public HuffNode<E> {//内部结点
private:
	HuffNode<E>* lc;//Left child
	HuffNode<E>* rc;//Right child
	int wgt;//Subtree weight
public:
	IntlNode(HuffNode<E>*l, HuffNode<E>*r) {
		wgt = l->weight() + r->weight();//结点的权重为左子树权重+右子树权重
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


/*Huffman树的类说明*/  
template <typename E> class HuffTree {
private:
	HuffNode<E>* Root;
public:
	HuffTree(E& val, int freq) {//构造叶子结点
		Root = new LeafNode<E>(val, freq);
	}
	HuffTree(HuffTree<E>* l, HuffTree<E>*r) {//构造内部结点
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


/*Huffman树构造函数的实现*/
template<typename E> class minTreeComp {
public:
	static bool prior(HuffTree<E>* a, HuffTree<E>* b) {
		return b->weight() >= a->weight();
	}
};

template <typename E> HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count) {
	heap<HuffTree<E>*, minTreeComp<E>>* forest = new heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);//初始化新的最小堆forest

	HuffTree<char> *temp1, *temp2, *temp3 = NULL;
	while (forest->size() > 1) {
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();//去除最前面的两棵子树
		temp3 = new HuffTree<E>(temp1, temp2);//产生新的根结点
		forest->insert(temp3);//将新的树插入线性表
		delete temp1;
		delete temp2;	
	}
	return temp3;
}

//template<typename E> void traverse(HuffNode<E>* forest, char outFile[]) {//遍历输出
//	ofstream out;
//	out.open(outFile, ios::app);
//	if (forest->isLeaf() == true) {
//		if (!out) {
//			cout << "创建文件失败" << endl;
//			return;
//		}
//		if (((LeafNode<E>*)forest)->val() == "\n") {
//			out<< "换行符 : " << forest->weight() << endl;
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
