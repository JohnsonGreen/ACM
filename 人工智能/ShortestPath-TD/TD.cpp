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

double a = 0.5;                              //阿尔法
double gama = 1.0;                           //伽马值

int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int r = -1;                                 //每次action的奖励
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
	S[3][3] = 'E';                          //终点
	S[2][1] = 'E';
	setPi();                               //设置初始的PI值
}

bool end(int s) {
	return S[s / 4][s % 4] == 'E';
}

int getNextByPi(int s) {

	double temp = (rand() % 10000) / 10000.0;
	int k = 4, i = s / MAX_M, j = s % MAX_M;
	double l = 0.0, r;
	int sb;
	while (k--) {
		int x = i + dx[k], y = j + dy[k];
		if (judge(x,y)) {
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

int getInitState() {
	int st = rand() % 16;
	while (true) {
		if (S[st / 4][st % 4] != '#' && S[st / 4][st % 4] != 'E') {
			break;
		}
		else {
			st = rand() % 16;
		}
	}
	return st;
}

void printV() {
	for (int i = 0; i < MAX_M; i++) {
		for (int j = 0; j < MAX_M; j++) {

			if (V[i][j] - 0 > e) {
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
double getMaxQ(int s) {
	int i = s / 4, j = s % 4, t = 4, rsflag;
	double ma = -INF;
	while (t--) {
		int x = i + dx[t], y = j + dy[t];
		if (judge(x, y)) {
			int rs = x * MAX_M + y;
			if (Q[s][rs] > ma) {
				ma = Q[s][rs];	
				rsflag = rs;
			}
		}
	}
	V[i][j] = Q[s][rsflag];
	t = 4;
	while (t--) {
		int x = i + dx[t], y = j + dy[t];
		if (judge(x, y)) {
			int rs = x * MAX_M + y;
			if (rs == rsflag) {
				PI[s][rs] = 1 - epi + epi / C[s];             //概率分配
			}
			else {
				PI[s][rs] = epi / C[s];
			}
		}
	}
	return ma;
}

void solve() {
	int mn = 0;
	while (true) {
		mn++;
		printf("-------------------%d---------------------", mn);
		int st = getInitState();
		printf("\n episodes:  %d ", st);
		do {
			int rt = getNextByPi(st);
			printf("%d ", rt);
			double MaxQ = getMaxQ(rt);
			Q[st][rt] += a * (r + gama * MaxQ - Q[st][rt]);         //更新Q值
			st = rt;	

		} while (!end(st));
	
		printf("\n");
		printV();
		printf("\n");

	}
}

int main() {
	srand(time(0));
	init();
	solve();
	return 0;
}