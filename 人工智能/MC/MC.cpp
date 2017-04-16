#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <Windows.h>
#include <time.h>
#include <cmath>

using namespace std;

const int MAX_M = 4;                       //���󳤿�
const int MAX_N = MAX_M * MAX_M;           //״̬����
const double INF = 999999999.0;
char   S[MAX_M][MAX_M];                    //״̬����
double V[MAX_M][MAX_M];                    //value����
double SA[MAX_N];                          //����ѡ���ĳ��״̬��Gֵ�ܺ�
double PI[MAX_N][MAX_N];                   //ѡ��action�ĸ���
int C[MAX_N];                              //״̬s�ܹ���ȡ���ж�����
int CNT[MAX_N];                           //����״̬�Ĵ�����������ƽ��


int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int r = -1;                                 //ÿ��action�Ľ���
double e = 1e-10;
double epi = 0.5;                          //episilon
queue<pair<int, int>> q;                   //����episode

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
	//memset(Q,0,sizeof(int)*MAX_N);      //��ʼ��
	//S[2][3] = '#';                        //�ϰ�
	S[3][3] = 'E';                        //�յ�
	setPi();                              //���ó�ʼ��PIֵ

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
		sb = x * MAX_M + y;
		if (fabs(PI[s][sb] - 0.0) < e)
			continue;
		r = l + PI[s][sb];
		if ((temp > l  &&  temp < r) || (fabs(temp - l) < e  &&  temp < r) || (fabs(temp - r) < e  &&  temp > r)) {
			return sb;
		}
		l = r;
	}
	return sb;
}

void makeEpisodeRandomly() {
	srand(time(0));
	int st = rand() % 16;
	printf("�������");
	while (true) {
		if (S[st / 4][st % 4] != '#' && S[st / 4][st % 4] != 'E') {
			break;
		}
		else {
			st = rand() % 16;
		}
	}
	int lt;
	do {
		printf("%d ",st);
		lt = getNextByPi(st);
		q.push(pair<int, int>(st, lt));
		st = lt;
	} while (!end(lt));

}

void print(double arr[][MAX_M]) {

	for (int i = 0; i < MAX_M; i++) {
		for (int j = 0; j < MAX_M; j++) {

			if (arr[i][j] - 0 > e) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA); //����
				printf("%.2lf ", arr[i][j]);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				printf("%.2lf ", arr[i][j]);
			}
		}
		puts("\n");
	}
}

void solve(){
     int k = 0;
	 while (true) {
		k++;
		makeEpisodeRandomly();
		printf("---------------------  %d  ----------------------\n", k);
		printf("���У� ");
		while (!q.empty()) {
			int G = q.size() * r;                            //����
			pair<int, int> p = q.front(); q.pop();
			int ls = p.first;
			printf("%d ", ls);
			int x = ls / MAX_M, y = ls % MAX_M;
			CNT[ls]++;                    //������1
			SA[ls] += G;
			V[x][y] = SA[ls] / CNT[ls];
		}
		puts("");
		print(V);
		puts("");
	}

}



int main() {

	init();
	solve();
	//print(V);

	return 0;
}