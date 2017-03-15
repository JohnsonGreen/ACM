#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;


//���е�˳��洢�ṹ
const int MaxSize = 50;

typedef int ElemType;


typedef struct {
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;

void InitQueue(SqQueue &q) {
	q.front = q.front = 0;
}

bool QueueEmpty(SqQueue q) {
	return q.rear == q.front;
}

bool EnQueue(SqQueue &q,ElemType x) {
	if ((q.rear + 1) % MaxSize == q.front)
		return false;
	q.data[q.rear] = x;
	q.rear = (q.rear + 1) % MaxSize;
	return true;
}

bool DeQueue(SqQueue &q, ElemType &x) {
	if (q.front == q.rear)   //����Ϊ��
		return false;
	x = q.data[q.front];
	q.front = (q.front + 1) % MaxSize;
	return true;
}

