/**
 ��n�����ÿ����ֱ���siʱ�俪ʼ����tiʱ�����������ÿ������㶼����ѡ�����������ѡ���˲��룬
 ��ô��ʼ���ն�����ȫ�̲��롣���⣬���빤����ʱ��β����ص�����ʼ˲��ͽ���˲����ص�Ҳ������

*/

/**
˼·���ڿ�ѡ�Ĺ�����ÿ�ζ�ѡȡ����ʱ������Ĺ���

*/


#include <cstdio>
#include <algorithm>


using namespace std;

typedef pair<int, int>  P;

P work[100009];
int n, s[100009], t[100009];


int solve() {
	for (int i = 0; i < n; i++) {
		work[i].first = t[i];    //������ʱ�����ǰ������
		work[i].second = s[i];
	}

	sort(work, work + n);  //��pair��������ʱĬ���ֵ�������Ҳ����first

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