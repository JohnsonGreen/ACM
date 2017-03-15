#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode {
	ElemType data;        //数据域
	struct LNode  *pre, *next;   //前驱和后继指针  
}LNode, *LinkList;




//1.采用头插法建立单链表
LinkList creatList(LinkList &L) {
	LNode *s; int x;
	L = (LinkList)malloc(sizeof(LNode));  //创建头结点
	L->next = NULL;     //初始为空链表
	scanf("%d", &x);   //输入结点的值
	while (x != 9999) {   //输入9999表示结束
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;  //把头节点后面的链表加在新插入节点的后面
		L->next = s;        //修改头节点的指针到s
		scanf("%d", &x);
	}
	return L;
}

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

//3.按序号查找节点值
LNode* getElem(LinkList L, int i) {

	if (i == 0)  return L;
	if (i < 0) return NULL;  //值无效

	int j = 1;             //第一个结点
	LNode* p = L->next;   //p为第一个结点指针
	while (p&&j < i) {
		p = p->next;
		j++;
	}
	return p;   //当j==i时返回结点，如果i > 总长度，则返回NULL
}


//4.按值查找结点值
LNode* locateElem(const LinkList L, ElemType x) {
	LNode* p = L->next;
	while (p != NULL && p->data != x)
		p = p->next;
	return p;      //找到则返回指向该节点的指针，没有找到则返回NULL
}

//5.插入结点操作(在结点i后插)
LNode* insertNode(LinkList& L, ElemType e, int i) {

	LNode* p = getElem(L, i);
	if (p == NULL)
		return NULL;

	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return s;
}

//6.删除结点操作
bool deleteElem(LinkList& L, int i) {
	LNode* p = getElem(L, i - 1);
	if (p == NULL)  return false;

	LNode* q = p->next;
	if (q != NULL) {       //q不是最后一个结点
		p->next = q->next;
		free(q);  //释放所占的内存空间
		return true;
	}

	return false;   //节点不存在，删除失败
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


int main() {

	LinkList L;
	creatList2(L);
	printLinkList(L);


	while (true) {

		/*
		int tm1, tm2;
		scanf("%d", &tm1);

		LNode* s = locateElem(L, tm1);
		if (s != NULL)
		printf("s:  %d\n", s->data);
		else
		puts("s为空");

		scanf("%d", &tm2);
		LNode* t = getElem(L, tm2);
		if (t != NULL)
		printf("t:  %d\n", t->data);
		else
		puts("t为空");
		*/


		/*
		int i;
		ElemType elem;
		scanf("%d%d", &elem, &i);
		insertNode(L, elem, i);
		printLinkList(L);
		*/

		int i;
		scanf("%d", &i);
		printf("bool:  %d\n", deleteElem(L, i));
		printLinkList(L);

	}




	return 0;
}
