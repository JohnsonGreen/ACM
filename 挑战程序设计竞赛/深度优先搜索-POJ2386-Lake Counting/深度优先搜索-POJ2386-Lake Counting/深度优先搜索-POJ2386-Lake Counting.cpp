
#include <cstdio>


using namespace std;


const int MAX_N = 110;

int n, m,res;
char field[MAX_N][MAX_N];

void dfs(int x, int y) {

	field[x][y] = '.';
	for (int dx = -1; dx <= 1; dx++) {
		int nx = x + dx;
		for (int dy = -1; dy <= 1; dy++) {
			int ny = y + dy;
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && field[nx][ny] == 'W')
				dfs(nx, ny);
		}
	}
		
}

void solve() {

	
	res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
		
			if(field[i][j] == 'W') {
				dfs(i, j);
				res++;
			}
		}
	}

}


int main() {

	scanf("%d %d", &n, &m);

	getchar();  //³Ôµô»»ÐÐ·û
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {  
			scanf("%c", &field[i][j]);
		}
		getchar();
	}

	solve();

	printf("%d\n", res);

	return 0;
}