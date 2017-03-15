#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

//栈的顺序存储结构
#define MaxSize 50           //定义栈中最大元素
typedef int ElemType;
typedef struct{
	ElemType data[MaxSize];   //存放栈中元素
	int top;      //栈顶指针
}SqStack;

//栈的链式存储结构,头插法
typedef struct Linknode{
	ElemType data;
	struct Linknode *next;   //指针域
}*LinkStack;    //栈类型定义



typedef struct LNode {

	char data;
	struct LNode *next;

}*LinkedList;

void creatLinkedList(LinkedList &L) {
	char ch = getchar();
	L = (LinkedList)malloc(sizeof(LNode));
	
	LNode *p,*r = L;     //尾插法需要尾指针
	while (ch != '\n') {
		p = (LNode*)malloc(sizeof(LNode));
		p->data = ch;
		r->next = p;
		r = p;
		ch = getchar();
	}
	r->next = NULL;

}


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

//判断IO组成的入栈出栈序列是否合法
bool isLegal(char s[],int n){
	int curIn = 0;    //当前入栈数
	int curOut = 0;   //当前出栈数
	for (int i = 0; i < n; i++) {
		
		if (s[i] == 'I') {
			curIn++;
		}
		else {
			curOut++;
		}
		if (curOut > curIn)
			return false;
	}

	if (curIn != curOut)    //当前出入栈数必须一致，否则导致栈不为空
		return false;

	return true;
}

//4.设单链表的表头指针为h，节点结构由data和next两个域组成，其中data欲为字符型，试设计算法判断该链表前n个字符是否中心对称
bool dc( LinkedList L, int n) {

	if (n <= 1)        //n的值不合法，n必须大于会等于2才考虑对称性
		return false;

	LNode *p = L->next;
	char arr[MaxSize];       //字符栈
	int top = -1;           //栈顶指针
	while (p != NULL && top < (n / 2 - 1)) {
		arr[++top] = p->data;
		p = p->next;
	}

	if (p == NULL)    //链表总长度<=n/2,不满足条件
		return false;

	if (n & 1)           //n为奇数
		p = p->next;          //忽略中间数
	
	while (p != NULL && top > -1) {
		if (p->data != arr[top--])
			return false;
		p = p->next;
	}

	if (top > -1)       //栈未被清空，说明字符总数不到n个
		return false;
	else
		return true;
	
}

void printList(LinkedList &L) {
	LNode *p = L->next;
	while (p) {
		cout << p->data;
		p = p->next;
	}
	cout << endl;
}



int temp(int a){

	int i = 0;
	while (a != 0) {
		if (a & 1) {
			i++;
		}
		a >>= 1;
	}
	return i;
}


int main() {

	
	/*  
	int i = 10;
	SqStack s;
	InitStack(s);
	while (i--) {
		ElemType e;
		scanf("%d", &e);
		Push(s, e);
	}

	prinStack(s);
	*/

	/* 
	while (true) {
		char str[50];
		int n = 0;
		while (1) {
			char a = getchar();
			if (a != '\n') {
				str[n++] = a;
			}
			else
				break;
		}
		
		cout << isLegal(str,n) << endl;
	}
	 */

	LinkedList L;
	creatLinkedList(L);
	printList(L);
	while (1) {
		int n;
		scanf("%d", &n);
		cout << dc(L, n) << endl;
	}

	


	

	return 0;
}