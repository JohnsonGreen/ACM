#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

typedef int ElemType;
typedef struct ThreadNode {
	ElemType data;        //������
	struct ThreadNode *lchild, *rchild;  //���Һ���ָ��
	int ltag, rtag;           //����������־��0�����ӽ�㣬1Ϊָ��ǰ�����ߺ�̽��
}ThreadNode, *ThreadTree;


//�����������Ĺ��죬���������м�鵱ǰ�������ָ�����Ƿ�Ϊ�գ���Ϊ�գ������Ǹ�Ϊָ��ǰ�������ߺ�����������
//�������������������
void InThread(ThreadTree &p, ThreadTree &pre) {
	if (p != NULL) {
		InThread(p->lchild, pre);  //�ݹ飬������������
		if (p->lchild == NULL) {   //������Ϊ�գ�����ǰ������
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL&&pre->rchild == NULL) {
			pre->rchild = p;             //����ǰ�����ĺ������
			pre->rtag = 1;
		}
		pre = p;                     //��ǵ�ǰ���Ϊ�ոշ��ʹ��Ľ��
		InThread(p->rchild, pre);    //�ݹ�������������
	}
}

void CreateInthread(ThreadTree T) {
	ThreadTree pre = NULL;
	if (T != NULL) {
		InThread(T, pre);    //�ǿն�������������
		pre->rchild = NULL;      //�������������һ�����
		pre->rtag = 1;
	}
}


//�����������ı��������ֱ������ٽ���ջ
//�������������������������µĵ�һ�����,��һ����Ҷ�ӽ��
ThreadNode *FirstNode(ThreadNode *p) {
	while (p->ltag == 0) p = p->lchild;
	return p;
}

//���������������н��p�����������µĺ�̽��
ThreadNode *NextNode(ThreadNode *p) {
	if (p->rtag == 0) return FirstNode(p->rchild);
	else return p->rchild;    //rtag==1ֱ�ӷ��غ������
}
//���һ�����
ThreadNode *GetLast(ThreadNode *p) {
	while(p->rtag == 0) p = p->rchild;
	 return p;
}
//����ͷ������������������㷨
void InOrder(ThreadNode *T) {
	for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
		visit(p);
}


void visit(ThreadNode *b) {
	printf("%d ", b->data);
}
