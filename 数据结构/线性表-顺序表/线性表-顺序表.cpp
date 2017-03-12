#include <cstdio>

using namespace std;


typedef  int ElemType;
const int MAX = 100;


typedef struct {
	ElemType data[MAX];
	int length;    //��ǰ���Ա�ĳ���
	
}SqList;


ElemType A[10] = {1,5,6,2,    0,2,5,2,6,9};  //���Ա�4+6



/*
8.��֪��һά����A[m+n]��һ�����������Ա���дһ��������������˳����λ�û�����
˼·���Ƚ���������ԭ���û�����m��n�û����ڶ�m��n�����ڲ��û���

*/

void reverse(ElemType A[],int left, int right,int arraySize) {
	if (left >= right || right >= arraySize)
		return;
	int mid = (left + right) / 2;
	for (int i = 0; i <= mid - left; i++) {
		ElemType temp = A[left + i];
		A[left + i] = A[right - i];
		A[right - i] = temp;
	}
}

void Exchange(ElemType A[],int m,int n,int arraySize) {
	reverse(A,0,m+n-1,arraySize);
	reverse(A, 0, n - 1, arraySize);
	reverse(A, n, m + n - 1, arraySize);
}

/*
 9.���Ա�(a1,a2..an)����������������ʱ���ڱ��в�����ֵΪx��Ԫ�أ����ҵ�����������Ԫ�ؽ��������Ҳ������������в�ʹ����Ԫ������

*/

bool findOrInsert(ElemType A[], ElemType x,int n) {
	int low = 0, high = n - 1,mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (A[mid] == x) {
			if (mid != n - 1) {     //�������������ܰѴ������������if��&&���ӣ�����������ѭ��
				ElemType temp = A[mid];
				A[mid] = A[mid + 1];
				A[mid + 1] = temp;
			}
			return true;
		}
		else if (A[mid] < x)
			low = mid + 1;
		else if (A[mid] > x)
			high = mid - 1;
	}

	//δ�ҵ���low�Ѿ�����high��A[high] < x,��A[low] Ҫô����x��Ҫô�����ڣ�low == n����x�ض������뵽�±�high֮��
	for (int i = n - 1; i > high; i--)
		A[i + 1] = A[i];

	A[high + 1] = x;   //����x��high֮��
	return false;
}

/*
11.��һ������ΪL(L>=1)����������S�������±�Ϊn-1/2����Ϊ��λ���������������ȳ�����A��B�������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨���ҳ���������A��B����λ��
���˼�룺
   �ֱ���������������A\B����λ������Ϊa��b��
   1.��a=b,��a��b��Ϊ������λ�����㷨����
   2.��a<b,����������A�н�С��һ�룬ͬʱ��������B�нϴ��һ�룬Ҫ�����������ĳ������
   3.��a>b,����������B�н�С��һ�룬ͬʱ��������A�нϴ��һ�룬Ҫ�����������ĳ�����ȡ�

  �ڱ������������������У��ظ�����1��2��3��ֱ�����������о�ֻ��һ��Ԫ��Ϊֹ����С�߼�Ϊ�������λ��

*/




int main() {


	//Exchange(A, 5, 5, 10);

	ElemType a[100];
	ElemType b[100];
	int n,x;
	
	while (true)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
			
		while (true) {
			puts("find: ");
			scanf("%d", &x);
			int res = findOrInsert(a, x, n);
			printf("res: %d \n", res);
			for (int i = 0; i < n + 1 ; i++) {
				printf("%d  ", a[i]);
			}
			puts("");
			for (int i = 0; i < n; i++)
				a[i] = b[i];
		}
		
	}

	
	


	return 0;
}