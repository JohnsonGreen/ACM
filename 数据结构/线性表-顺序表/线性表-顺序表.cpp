#include <cstdio>

using namespace std;


typedef  int ElemType;
const int MAX = 100;


typedef struct {
	ElemType data[MAX];
	int length;    //当前线性表的长度
	
}SqList;


ElemType A[10] = {1,5,6,2,    0,2,5,2,6,9};  //线性表4+6



/*
8.已知在一维数组A[m+n]中一次有两个线性表，编写一个函数，将两个顺序表的位置互换。
思路：先将数组整体原地置换，即m与n置换，在对m和n进行内部置换。

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
 9.线性表(a1,a2..an)递增有序请在最少时间在表中查找数值为x的元素，若找到，将其与后继元素交换，若找不到将其插入表中并使表中元素有序

*/

bool findOrInsert(ElemType A[], ElemType x,int n) {
	int low = 0, high = n - 1,mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (A[mid] == x) {
			if (mid != n - 1) {     //交换条件，不能把此条件跟上面的if用&&连接，否则会造成死循环
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

	//未找到则low已经大于high，A[high] < x,而A[low] 要么大于x，要么不存在（low == n）即x必定被插入到下标high之后
	for (int i = n - 1; i > high; i--)
		A[i + 1] = A[i];

	A[high + 1] = x;   //插入x到high之后
	return false;
}

/*
11.在一个长度为L(L>=1)的升序序列S，处在下标为n-1/2的数为中位数，现在有两个等长序列A和B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数
设计思想：
   分别求两个升序序列A\B的中位数，设为a和b，
   1.若a=b,即a或b即为所求中位数，算法结束
   2.若a<b,则舍弃序列A中较小的一半，同时舍弃序列B中较大的一半，要求两次舍弃的长度相等
   3.若a>b,则舍弃序列B中较小的一半，同时舍弃序列A中较大的一半，要求两次舍弃的长度相等。

  在保留的两个升序序列中，重复过程1）2）3）直到两个序列中均只含一个元素为止，较小者即为所求的中位数

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