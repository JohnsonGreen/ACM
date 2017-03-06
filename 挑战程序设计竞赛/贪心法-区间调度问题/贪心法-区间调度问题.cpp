/**
 有n项工作，每项工作分别在si时间开始，在ti时间结束。对于每项工作，你都可以选择参与与否，如果选择了参与，
 那么自始至终都必须全程参与。此外，参与工作的时间段不能重叠（开始瞬间和结束瞬间的重叠也不允许）

*/

/**
思路：在可选的工作中每次都选取结束时间最早的工作

*/


#include <cstdio>
#include <algorithm>


using namespace std;

typedef pair<int, int>  P;

P work[100009];
int n, s[100009], t[100009];


int solve() {
	for (int i = 0; i < n; i++) {
		work[i].first = t[i];    //将结束时间放在前面排序
		work[i].second = s[i];
	}

	sort(work, work + n);  //对pair数组排序时默认字典序排序，也就是first

	int ans = 0, t = 0;

	for (int i = 0; i < n; i++) {
		if (t < work[i].second) {
			ans += 1;
			t = work[i].first;
		}

	}

	return ans;


}

int main() {

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &s[i]);
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &t[i]);
	}


	printf("%d\n", solve());

	return 0;
}