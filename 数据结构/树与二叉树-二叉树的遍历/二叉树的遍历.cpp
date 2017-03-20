#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef int ElemType;
typedef struct BitNode {
	ElemType data;        //������
 	struct BitNode *lchild, *rchild;  //���Һ���ָ��
}BitNode,*BitTree;

void visit(BitNode *b) {
	printf("%d ", b->data);
}

//���۲������ֱ���������ʱ�临�Ӷȶ���O(n)����Ϊÿ����㶼����һ���ҽ�����һ�Σ��ݹ鹤��ջ��ջ��ǡ��Ϊ������ȣ��ռ临�Ӷ�ΪO(n)
//�������������
void PreOrder(BitTree T) {
	if (T != NULL) {
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	  }
}
//������������
void InOrder(BitTree T) {
	if (T != NULL) {
		InOrder(T->lchild);
		visit(T);
		InOrder(T->rchild);
	 }
}

//������������
void PostOrder(BitTree T) {
	if (T != NULL) {
		PostOrder(T->lchild);	
		PostOrder(T->rchild);
		visit(T);
	}
}

//�ݹ��㷨ת��Ϊ�ǵݹ�,
void Inorder2(BitTree T) {
	stack<BitTree> s; BitTree p = T;
	while (p != NULL || !s.empty()) {   //ջ����ʱ��p����ʱѭ��
		if (p) {
			s.push(p);
			p = p->lchild;
			
		}
		else {
			p = s.top; s.pop();    //����ʱ��pû����ָ��
			visit(p);
			p = p->rchild;
		}
	}
}

//��������α���,��������
void LevelOrder(BitTree T) {
	queue<BitTree> q; BitTree p = T;
	q.push(p);
	while (!q.empty) {
		p = q.front; q.pop();
		visit(p);
		if (p->lchild)
			q.push(p->lchild);   //���������գ������������
		if (p->rchild)
			q.push(p->rchild);
	}
}

