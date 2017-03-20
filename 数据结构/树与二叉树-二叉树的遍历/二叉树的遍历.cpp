#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef int ElemType;
typedef struct BitNode {
	ElemType data;        //数据域
 	struct BitNode *lchild, *rchild;  //左右孩子指针
}BitNode,*BitTree;

void visit(BitNode *b) {
	printf("%d ", b->data);
}

//无论采用哪种遍历方法，时间复杂度都是O(n)，因为每个结点都访问一次且仅访问一次，递归工作栈的栈深恰好为树的深度，空间复杂都为O(n)
//先序遍历根左右
void PreOrder(BitTree T) {
	if (T != NULL) {
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	  }
}
//中序遍历左根右
void InOrder(BitTree T) {
	if (T != NULL) {
		InOrder(T->lchild);
		visit(T);
		InOrder(T->rchild);
	 }
}

//后序遍历左根右
void PostOrder(BitTree T) {
	if (T != NULL) {
		PostOrder(T->lchild);	
		PostOrder(T->rchild);
		visit(T);
	}
}

//递归算法转换为非递归,
void Inorder2(BitTree T) {
	stack<BitTree> s; BitTree p = T;
	while (p != NULL || !s.empty()) {   //栈不空时或p不空时循环
		if (p) {
			s.push(p);
			p = p->lchild;
			
		}
		else {
			p = s.top; s.pop();    //弹出时，p没有左指针
			visit(p);
			p = p->rchild;
		}
	}
}

//二叉树层次遍历,借助队列
void LevelOrder(BitTree T) {
	queue<BitTree> q; BitTree p = T;
	q.push(p);
	while (!q.empty) {
		p = q.front; q.pop();
		visit(p);
		if (p->lchild)
			q.push(p->lchild);   //左子树不空，则左子树入队
		if (p->rchild)
			q.push(p->rchild);
	}
}

