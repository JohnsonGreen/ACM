#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef int ElemType;
typedef struct ThreadNode {
	ElemType data;        //数据域
	struct ThreadNode *lchild, *rchild;  //左右孩子指针
	int ltag, rtag;           //左右线索标志，0，孩子结点，1为指向前驱或者后继结点
}ThreadNode, *ThreadTree;


//线索二叉树的构造，遍历过程中检查当前结点左右指针域是否为空，若为空，将它们改为指向前驱结点或者后驱结点的线索
//中序遍历二叉树线索化
void InThread(ThreadTree &p, ThreadTree &pre) {
	if (p != NULL) {
		InThread(p->lchild, pre);  //递归，线索化左子树
		if (p->lchild == NULL) {   //左子树为空，建立前驱线索
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL&&pre->rchild == NULL) {
			pre->rchild = p;             //建立前驱结点的后继线索
			pre->rtag = 1;
		}
		pre = p;                     //标记当前结点为刚刚访问过的结点
		InThread(p->rchild, pre);    //递归线索化右子树
	}
}

void CreateInthread(ThreadTree T) {
	ThreadTree pre = NULL;
	if (T != NULL) {
		InThread(T, pre);    //非空二叉树，线索化
		pre->rchild = NULL;      //处理遍历后的最后一个结点
		pre->rtag = 1;
	}
}


//线索二叉树的遍历，这种遍历不再借助栈
//求中序线索二叉树中序序列下的第一个结点,不一定是叶子结点
ThreadNode *FirstNode(ThreadNode *p) {
	while (p->ltag == 0) p = p->lchild;
	return p;
}

//中序线索二叉树中结点p在中序序列下的后继结点
ThreadNode *NextNode(ThreadNode *p) {
	if (p->rtag == 0) return FirstNode(p->rchild);
	else return p->rchild;    //rtag==1直接返回后继线索
}
//最后一个结点
ThreadNode *GetLast(ThreadNode *p) {
	while(p->rtag == 0) p = p->rchild;
	 return p;
}
//不含头结点的中序遍历二叉树算法
void InOrder(ThreadNode *T) {
	for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
		visit(p);
}


void visit(ThreadNode *b) {
	printf("%d ", b->data);
}
