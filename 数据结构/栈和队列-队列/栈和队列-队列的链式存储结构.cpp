#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;


//队列的顺序存储结构
const int MaxSize = 50;

typedef int ElemType;

typedef struct{
	ElemType data;
	LinkNode *next;
}LinkNode;    //注意不是指针

typedef struct {
	LinkNode *front, *rear;
}LinkQueue;

void InitQueue(LinkQueue &q) {
	q.rear = q.front = (LinkNode*)malloc(sizeof(LinkNode));
	q.front->next = NULL;
}

bool QueueEmpty(LinkQueue q) {
	return q.rear == q.front;
}

void EnQueue(LinkQueue &q,ElemType x) {
	LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
	p->data = x;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
}

bool DeQueue(LinkQueue &q, ElemType &x) {
	if (q.rear == q.front)
		return false;
	LinkNode *p = q.front->next;
	x = p->data;
	q.front->next = p->next;
	if (p == q.front)    //只有一个元素的时候要置尾指针为空
		q.rear = q.front;    
	free(p);
	return true;
}