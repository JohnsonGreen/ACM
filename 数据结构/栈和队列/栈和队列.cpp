#include <cstdlib>
#include <cstdio>

using namespace std;

//ջ��˳��洢�ṹ
#define MaxSize 50           //����ջ�����Ԫ��
typedef int ElemType;
typedef struct{
	ElemType data[MaxSize];   //���ջ��Ԫ��
	int top;      //ջ��ָ��
}SqStack;

void InitStack(SqStack &S) {
	S.top = -1;
}

bool StackEmpty(SqStack S) {
	return S.top == -1;
}

bool Push(SqStack &S, ElemType x) {
	if (S.top == MaxSize - 1)
		return false;
	S.data[++S.top] = x;
	return true;
}

bool Pop(SqStack &S, ElemType &x) {
	if (!(StackEmpty(S))) {
		x = S.data[S.top--];
		return true;
	}
	return false;
}

bool Gertop(SqStack S, ElemType &x) {
	if (S.top == -1)
		return false;
	x = S.data[S.top];
	return true;
}

bool ClearStack(SqStack &S) {
	if (S.top == -1)
		return false;

	S.top = -1;   //���ջ
	return true;
}

void prinStack(SqStack S) {
	
	ElemType x;
	
	while (!StackEmpty(S)) {
		Pop(S, x);
		printf("%d ", x);
	}

}


int main() {

	int i = 10;
	SqStack s;
	InitStack(s);
	while (i--) {
		ElemType e;
		scanf("%d", &e);
		Push(s, e);
	}

	prinStack(s);





	return 0;
}