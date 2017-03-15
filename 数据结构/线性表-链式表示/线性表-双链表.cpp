#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode {
	ElemType data;        //������
	struct LNode  *pre, *next;   //ǰ���ͺ��ָ��  
}LNode, *LinkList;




//1.����ͷ�巨����������
LinkList creatList(LinkList &L) {
	LNode *s; int x;
	L = (LinkList)malloc(sizeof(LNode));  //����ͷ���
	L->next = NULL;     //��ʼΪ������
	scanf("%d", &x);   //�������ֵ
	while (x != 9999) {   //����9999��ʾ����
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		s->next = L->next;  //��ͷ�ڵ�������������²���ڵ�ĺ���
		L->next = s;        //�޸�ͷ�ڵ��ָ�뵽s
		scanf("%d", &x);
	}
	return L;
}

//2.����β�巨����������
//��������һ��β��ָ�룬ʹ��ʼ��ָ��ǰ�����β���
LinkList creatList2(LinkList &L) {

	L = (LinkList)malloc(sizeof(LNode));
	LNode *r = L, *s;   //rΪָ��β������ָ��
	int x;
	scanf("%d", &x);
	while (x != 9999) {
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		scanf("%d", &x);
	}
	r->next = NULL;    //���������һ����ָ����ΪNULL����ôָ���ֵ��δ֪�Ķ��Ҳ�����NULL���ڱ�����ӡ����ʱ��s->next != NULL�����������㣬���������δ֪�ڴ�����ݣ��Ӷ�ʹ�������
	return L;

}

//3.����Ų��ҽڵ�ֵ
LNode* getElem(LinkList L, int i) {

	if (i == 0)  return L;
	if (i < 0) return NULL;  //ֵ��Ч

	int j = 1;             //��һ�����
	LNode* p = L->next;   //pΪ��һ�����ָ��
	while (p&&j < i) {
		p = p->next;
		j++;
	}
	return p;   //��j==iʱ���ؽ�㣬���i > �ܳ��ȣ��򷵻�NULL
}


//4.��ֵ���ҽ��ֵ
LNode* locateElem(const LinkList L, ElemType x) {
	LNode* p = L->next;
	while (p != NULL && p->data != x)
		p = p->next;
	return p;      //�ҵ��򷵻�ָ��ýڵ��ָ�룬û���ҵ��򷵻�NULL
}

//5.���������(�ڽ��i���)
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

//6.ɾ��������
bool deleteElem(LinkList& L, int i) {
	LNode* p = getElem(L, i - 1);
	if (p == NULL)  return false;

	LNode* q = p->next;
	if (q != NULL) {       //q�������һ�����
		p->next = q->next;
		free(q);  //�ͷ���ռ���ڴ�ռ�
		return true;
	}

	return false;   //�ڵ㲻���ڣ�ɾ��ʧ��
}



//��ӡ����
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
		puts("sΪ��");

		scanf("%d", &tm2);
		LNode* t = getElem(L, tm2);
		if (t != NULL)
		printf("t:  %d\n", t->data);
		else
		puts("tΪ��");
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
