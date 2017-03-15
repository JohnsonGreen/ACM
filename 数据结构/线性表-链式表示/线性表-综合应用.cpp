#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode {
	ElemType data;        //数据域
	struct LNode *next;    //指针域 未初始化时，指针指向的空间不明（野指针），也就是说要显式分配内存或置为NULL
}LNode, *LinkList;




//2.采用尾插法建立单链表
//必须增加一个尾部指针，使它始终指向当前链表的尾结点
LinkList creatList2(LinkList &L) {

	L = (LinkList)malloc(sizeof(LNode));
	LNode *r = L, *s;   //r为指向尾部结点的指针
	int x;
	scanf("%d", &x);
	while (x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = NULL;    //如果不在这一步把指针置为NULL，那么指针的值是未知的而且不会是NULL，在遍历打印链表时（s->next != NULL）条件会满足，会继续访问未知内存的数据，从而使程序崩溃
	return L;
}

//打印链表
void printLinkList(const LinkList &L) {
	LNode * s = L;
	while (s->next != NULL) {
		printf("%d ", s->next->data);
		s = s->next;
	}
	puts("");
}





//1.设计一个递归算法，删除不带头节点的单链表L中所有值为x的结点。
void delx(LinkList& L, ElemType x) {

	if (L == NULL)
		return;

	if (L->data == x) {
		LNode *p = L;
		L = L->next;   //在c++中L为引用，不会断链
		free(p);
		delx(L, x);
	}
	else {
		delx(L->next, x);
	}
}

//2.在带头结点的单链表中，删除所有值为x的节点，并释放其空间，假设值为x的结点不唯一
void delx2(LinkList &L, ElemType x) {
	LNode *p = L->next;
	LNode *pre = L;
	while (p) {
		if (p->data == x) {
			pre->next = p->next;
			free(p);
			p = pre->next;
		}
		else {
			pre = p;
			p = p->next;
		}
	}
}

//3.设L为带头节点的单链表，编写算法实现从尾到头反向输出每个节点的值(王道书上的答案只适用于不带头节点的单链表，因此是错误的)
void printReverse(LinkList &L) {

	if (L->next == NULL)
		return;
	printReverse(L->next);
	printf("%d ", L->next->data);
	
}


//4.在带头结点的单链表L中删除一个最小值的高效算法（假设最小值是唯一的）
void delMin( LinkList & L) {
	LNode *p = L->next,*pre = L;
	ElemType mi;
	if(p)   mi = p->data;
	while (p) {
		if (p->next) {
			if (mi > p->next->data) {
				pre = p;
				mi = p->next->data;	
			}	
			p = p->next;
		}
		else {
			break;
		}
	}

	LNode *temp = pre->next;   //最小值
	if (temp != NULL) {
		pre->next = temp->next;
		free(temp);
	}
}


//5.试编写算法将带头节点的单链表就地逆置,辅助空间复杂度为O(1)
void reverse(LinkList& L) {

	LinkList head = L;

	LNode *p = L->next;
	LNode *s = L,*e = L;  //左为s

	while (p != NULL) {
		L->next
		 = p->next;
		p = temp->next;
        p
	}
}



int main() {

	LinkList L;
	creatList2(L);
	printLinkList(L);


	while (true) {

		int i;
		scanf("%d", &i);
		//delx2(L, i);

		delMin(L);

		//printReverse(L);
		printLinkList(L);

	}


	return 0;
}




