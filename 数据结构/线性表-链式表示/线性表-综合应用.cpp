#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode {
	ElemType data;        //������
	struct LNode *next;    //ָ���� δ��ʼ��ʱ��ָ��ָ��Ŀռ䲻����Ұָ�룩��Ҳ����˵Ҫ��ʽ�����ڴ����ΪNULL
}LNode, *LinkList;




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

//��ӡ����
void printLinkList(const LinkList &L) {
	LNode * s = L;
	while (s->next != NULL) {
		printf("%d ", s->next->data);
		s = s->next;
	}
	puts("");
}





//1.���һ���ݹ��㷨��ɾ������ͷ�ڵ�ĵ�����L������ֵΪx�Ľ�㡣
void delx(LinkList& L, ElemType x) {

	if (L == NULL)
		return;

	if (L->data == x) {
		LNode *p = L;
		L = L->next;   //��c++��LΪ���ã��������
		free(p);
		delx(L, x);
	}
	else {
		delx(L->next, x);
	}
}

//2.�ڴ�ͷ���ĵ������У�ɾ������ֵΪx�Ľڵ㣬���ͷ���ռ䣬����ֵΪx�Ľ�㲻Ψһ
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

//3.��LΪ��ͷ�ڵ�ĵ�������д�㷨ʵ�ִ�β��ͷ�������ÿ���ڵ��ֵ(�������ϵĴ�ֻ�����ڲ���ͷ�ڵ�ĵ���������Ǵ����)
void printReverse(LinkList &L) {

	if (L->next == NULL)
		return;
	printReverse(L->next);
	printf("%d ", L->next->data);
	
}


//4.�ڴ�ͷ���ĵ�����L��ɾ��һ����Сֵ�ĸ�Ч�㷨��������Сֵ��Ψһ�ģ�
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

	LNode *temp = pre->next;   //��Сֵ
	if (temp != NULL) {
		pre->next = temp->next;
		free(temp);
	}
}


//5.�Ա�д�㷨����ͷ�ڵ�ĵ�����͵�����,�����ռ临�Ӷ�ΪO(1)
void reverse(LinkList& L) {

	LinkList head = L;

	LNode *p = L->next;
	LNode *s = L,*e = L;  //��Ϊs

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




