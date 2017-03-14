#include <cstdlib>
#include <cstdio>

using namespace std;

//栈的顺序存储结构
#define MaxSize 50           //定义栈中最大元素
typedef int ElemType;
typedef struct{
	ElemType data[MaxSize];   //存放栈中元素
	int top;      //栈顶指针
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

	S.top = -1;   //清空栈
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