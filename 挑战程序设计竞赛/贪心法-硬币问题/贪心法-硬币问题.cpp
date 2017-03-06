/**
*有1元、5元、10元、50元、100元、500元的硬币各C1\C5\C10\C50\C100\C500枚。现在要用这些硬币来支付A元，最少需要多少枚
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