/**
*  ��ĳ��״̬��ʼ������ת��״ֱ̬���޷�ת�ƣ�Ȼ����˵�ǰһ����״̬��
*  ����ת�Ƶ�����״̬����˲����ظ���ֱ���ҵ����յĽ�
*
*/

/**
*  ����֤��a1\a2\a3\an���ж��Ƿ���Դ���ѡ����������ʹ���ǵĺ�ǡ��Ϊk
*  ˼·����ÿ���ڵ���ѡ�Ͳ�ѡ����ѡ��������dfs���������սڵ㣬����2^n�ֿ���
*
*/

#include <cstdio>



using namespace std;

const int MAX_N = 2 << 10;
int a[MAX_N];
int n, k;


bool dfs(int i, int sum) {
	

	if (i == n)      //��i==nʱ��˵��֮ǰ0��n-1���Ѿ���ȫ��������ʱӦ���жϺ��Ƿ���k�����
		return sum == k;

	//ѡ���i��,ֻ��������·����ȷʱ���Ż������ӡ
	if (dfs(i + 1, sum + a[i])) { 
		printf("%d ", a[i]);  
		return true; 
	}  

	//��ѡ���i��
	if (dfs(i + 1, sum))    return true;

	
	//ѡ�벻ѡ������
	return false;
}

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);

	}
	scanf("%d", &k);

	if (dfs(0, 0))  puts("Yes\n");
	else       puts("No\n");


	return 0;
}