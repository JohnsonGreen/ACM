/**
*  从某个状态开始，不断转移状态直到无法转移，然后回退到前一步的状态，
*  继续转移到其他状态，如此不断重复，直到找到最终的解
*
*/

/**
*  给定证书a1\a2\a3\an，判断是否可以从中选出若干数，使它们的和恰好为k
*  思路：对每个节点有选和不选两种选择，所以以dfs遍历到最终节点，共有2^n种可能
*
*/

#include <cstdio>



using namespace std;

const int MAX_N = 2 << 10;
int a[MAX_N];
int n, k;


bool dfs(int i, int sum) {
	

	if (i == n)      //当i==n时，说明之前0到n-1项已经完全遍历，此时应该判断和是否与k相等了
		return sum == k;

	//选择第i项,只有在整条路径正确时，才会逆序打印
	if (dfs(i + 1, sum + a[i])) { 
		printf("%d ", a[i]);  
		return true; 
	}  

	//不选择第i项
	if (dfs(i + 1, sum))    return true;

	
	//选与不选都不行
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