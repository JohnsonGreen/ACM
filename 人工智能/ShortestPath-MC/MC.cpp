#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <Windows.h>
#include <time.h>
#include <cmath>

using namespace std;

const int MAX_M = 4;                       //矩阵长宽
const int MAX_N = MAX_M * MAX_M;           //状态总数
const double INF = 999999999.0;         
char   S[MAX_M][MAX_M];                    //状态矩阵
double Q[MAX_N][MAX_N];                    //大脑
double SA[MAX_N][MAX_N];                   //保存选择的某个action的G值总和
double PI[MAX_N][MAX_N];                   //选择action的概率
int C[MAX_N];                              //状态s能够采取的行动数量
int CNT[MAX_N][MAX_N];                     //经过状态的次数，用于作平均
double V[MAX_M][MAX_M];                       //值矩阵

int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int r = -1;                                 //每次action的奖励
double gama = 0.8;
double e = 1e-10;
double epi = 0.8;                          //episilon
queue<pair<int, int>> q;                   //保存episode

bool judge(int x, int y) {
	return (x >= 0 && x < MAX_M && y >= 0 && y < MAX_M && S[x][y] != '#');
}

void setPi() {
	for (int i = 0; i < MAX_M; i++) {
		for (int j = 0; j < MAX_M; j++) {
			int cnt = 0, k = 4;
			while (k--) {
				int x = i + dx[k], y = j + dy[k];
				if (judge(x, y)) {
					cnt++;
				}
			}
			int t = 4, sa = i * MAX_M + j;
			C[sa] = cnt;
			while (t--) {
				int x = i + dx[t], y = j + dy[t];
				if (judge(x, y)) {
					int sb = x * MAX_M + y;
					PI[sa][sb] = 1.0 / cnt;
				}
			}
		}
	}
}

void  init() {
	
	//S[2][3] = '#';                        //障碍
	S[0][0] = 'E';                        //终点
	S[1][2] = 'E';
	S[1][4] = 'E';
	setPi();                              //设置初始的PI值

}

bool end(int s) {
	return S[s / 4][s % 4] == 'E';
}

int getNextByPi(int s) {

	double temp = (rand() % 10000)/10000.0;
	int k = 4,i = s / MAX_M, j = s % MAX_M ;
	double l = 0.0, r;
	int sb;
	while (k--) {
		int x = i + dx[k], y = j + dy[k];
		if (judge(x, y)) {
			sb = x * MAX_M + y;
			if (fabs(PI[s][sb] - 0.0) < e)
				continue;
			r = l + PI[s][sb];
			if ((temp > l  &&  temp < r) || (fabs(temp - l) < e  &&  temp < r) || (fabs(temp - r) < e  &&  temp > r)) {
				return sb;
			}
			l = r;
		}
	}
	return sb;
}

void makeEpisodeRandomly() {
	
	int st = rand() % MAX_N;
	while (true) {
		if (S[st/MAX_M][st % MAX_M] != '#' && S[st / MAX_M][st % MAX_M] != 'E') {
			break;
		}
		else {
			st = rand() % MAX_N;
		}
	}
	int lt;
	//printf("\n序列: ");
	//printf("%d  ", st);
	do{
		lt = getNextByPi(st);
		q.push(pair<int,int>(st,lt));
		st = lt;
	//	printf("%d  ", lt);
	} while (!end(lt));
	//printf("\n");
	
}

void printV() {
	for (int i = 0; i < MAX_M; i++) {
		for (int j = 0; j < MAX_M; j++) {
			if (fabs(V[i][j] - 0) > e) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA); //亮绿
				printf("%.2lf ", V[i][j]);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("%.2lf ", V[i][j]);
			}
		}
		printf("\n");
	}
}

void solve() {
	int mn = 0;
	int all = 1000;
	while (all--) {
		mn++;
		//printf("-------------------%d---------------------",mn);
		makeEpisodeRandomly();
		
		double G[MAX_N][MAX_N];
		for (int i = 0; i < MAX_N; i++) {
			for (int j = 0; j < MAX_N; j++) {
				G[i][j] = 0.0;
			}
		}

		int k = 0;
		queue<pair<int, int>> tq;
		while (!q.empty()) {
			pair<int, int> p = q.front(); tq.push(p); q.pop();
			int ls = p.first, rs = p.second;
			queue<pair<int, int>> tqr;
			if (fabs(G[ls][rs] - 0.0) > e) {
				continue;           //忽略以后的重复次数
			}
			G[ls][rs] = r;
			int pin = 0;
			while (!q.empty()) {
				pin++;
				pair<int, int> tp = q.front(); q.pop();
				tqr.push(tp);
				G[ls][rs] += r * (pow(gama, pin));                //奖励
			}
			q = tqr; 
			CNT[ls][rs]++;                    //次数加1
			SA[ls][rs] += G[ls][rs];
			Q[ls][rs] = SA[ls][rs] / CNT[ls][rs];
		}
		while (!tq.empty()) {
			pair<int, int> p = tq.front(); tq.pop();
			int ls = p.first;
			int i = ls / MAX_M, j = ls % MAX_M,t = 4,rsflag;
			double ma = -INF;
			while (t--){
				int x = i + dx[t], y = j + dy[t];
				if (judge(x, y)) {
					int rs = x * MAX_M + y;
					if (Q[ls][rs] > ma) {
						ma = Q[ls][rs];
						rsflag = rs;
					}
				}
			}
			V[i][j] = Q[ls][rsflag];
			t = 4;
			while (t--) {
				int x = i + dx[t], y = j + dy[t];
				if (judge(x, y)) {
					int rs = x * MAX_M + y;
					if (rs == rsflag) {
						PI[ls][rs] = 1 - epi + epi / C[ls];             //概率分配
					}
					else {
						PI[ls][rs] = epi / C[ls];
				    }
				}
			}
		}

		//printf("\n");
		//printV();
		//printf("\n");
	}

	printV();
	
}

int main() {
	srand(time(0));
	init();
	solve();
	  
	return 0;
}