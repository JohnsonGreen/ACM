/**
*��1Ԫ��5Ԫ��10Ԫ��50Ԫ��100Ԫ��500Ԫ��Ӳ�Ҹ�C1\C5\C10\C50\C100\C500ö������Ҫ����ЩӲ����֧��AԪ��������Ҫ����ö
*
*/


#include <cstdio>
#include <algorithm>


using namespace std;

const int v[6] = { 1,5,10,50,100,500 };
int c[6];
int a;

int solve() {

	int ans=0;
	for (int i = 5; i >= 0; i--) {
		int t = min(a / v[i], c[i]);
		a -= t*v[i];
		ans += t;
	}
	return ans;

}

int main() {

	for (int i = 0; i < 6; i++)
		scanf("%d", &c[i]);

	
	scanf("%d", &a);

	printf("%d\n", solve());

	return 0;
}