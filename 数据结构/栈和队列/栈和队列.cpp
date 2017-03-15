#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

//ջ��˳��洢�ṹ
#define MaxSize 50           //����ջ�����Ԫ��
typedef int ElemType;
typedef struct{
	ElemType data[MaxSize];   //���ջ��Ԫ��
	int top;      //ջ��ָ��
}SqStack;

//ջ����ʽ�洢�ṹ,ͷ�巨
typedef struct Linknode{
	ElemType data;
	struct Linknode *next;   //ָ����
}*LinkStack;    //ջ���Ͷ���



typedef struct LNode {

	char data;
	struct LNode *next;

}*LinkedList;

void creatLinkedList(LinkedList &L) {
	char ch = getchar();
	L = (LinkedList)malloc(sizeof(LNode));
	
	LNode *p,*r = L;     //β�巨��Ҫβָ��
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

//�ж�IO��ɵ���ջ��ջ�����Ƿ�Ϸ�
bool isLegal(char s[],int n){
	int curIn = 0;    //��ǰ��ջ��
	int curOut = 0;   //��ǰ��ջ��
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

	if (curIn != curOut)    //��ǰ����ջ������һ�£�������ջ��Ϊ��
		return false;

	return true;
}

//4.�赥����ı�ͷָ��Ϊh���ڵ�ṹ��data��next��������ɣ�����data��Ϊ�ַ��ͣ�������㷨�жϸ�����ǰn���ַ��Ƿ����ĶԳ�
bool dc( LinkedList L, int n) {

	if (n <= 1)        //n��ֵ���Ϸ���n������ڻ����2�ſ��ǶԳ���
		return false;

	LNode *p = L->next;
	char arr[MaxSize];       //�ַ�ջ
	int top = -1;           //ջ��ָ��
	while (p != NULL && top < (n / 2 - 1)) {
		arr[++top] = p->data;
		p = p->next;
	}

	if (p == NULL)    //�����ܳ���<=n/2,����������
		return false;

	if (n & 1)           //nΪ����
		p = p->next;          //�����м���
	
	while (p != NULL && top > -1) {
		if (p->data != arr[top--])
			return false;
		p = p->next;
	}

	if (top > -1)       //ջδ����գ�˵���ַ���������n��
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