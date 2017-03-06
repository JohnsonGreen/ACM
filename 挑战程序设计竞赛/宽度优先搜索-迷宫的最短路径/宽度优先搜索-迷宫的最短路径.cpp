
/*
* 给定一个大小为N x M的迷宫。迷宫由通道和墙壁组成，每一步可以像邻接的上下左右四格的通道移动。
* 请求出从起点到终点所需的最小步数
* 
*/

#include <cstdio>
#include <algorithm>   //包含pair
#include <queue>

using namespace std;

const int INF = 2 << 27;
typedef pair<int, int> p;

char maze[110][110];
int d[110][110];   //到各个点的距离

int n, m;
int sx, sy,ex,ey;

int dx[4] = { -1,0,1,0 }, dy[4] = { 0,-1,0,1 };

//求(sx,sy)到(ex,ey)的最短距离
//如果无法到达，则是INF

int bfs() {


	for(int i = 0; i < n;i++)
		for (int j = 0; j < m; j++) {
			d[i][j] = INF;

	}

	queue<p> que;
	que.push(p(sx, sy));
	
	d[sx][sy] = 0;


	while (que.size()) {

		p p1 = que.front();
		que.pop();

		//如果取出的点就是终点，直接退出
		if (p1.first == ex && p1.second == ey)
			break;

		int nx, ny;
		for (int i = 0; i < 4; i++) {
			nx = p1.first + dx[i], ny = p1.second + dy[i];
			
			if (nx < n && nx >= 0 && ny < m && ny >= 0 && maze[nx][ny] != '#' && d[nx][ny] == INF) {
				que.push(p(nx, ny));   //将没有被访问(不为INF)和可以到达（不为 #）的点加入队列
				d[nx][ny] = d[p1.first][p1.second] + 1;
				
			}
		}
	}
	return d[ex][ey];
}


int main() {


	scanf("%d %d", &n, &m);

	getchar();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char ch = getchar();
			if (ch == 'S') {
				sx = i;
				sy = j;
			}else if(ch == 'G'){
				ex = i;
				ey = j;
			}
			maze[i][j] = ch;
		}
		getchar();
	}

	int res = bfs();

	if (res != INF)
		printf("%d\n", res);
	else
		puts("INF");
		
	return 0;
}

