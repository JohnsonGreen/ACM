#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <Windows.h>

using namespace std;

const int MAX_N = 4;
const float INF = -999999999.0f;
float V[MAX_N][MAX_N];      //值矩阵
float OLDV[MAX_N][MAX_N];    //保存旧的val值
char S[MAX_N][MAX_N];      //状态矩阵，直观存储运动方向
						   //float P[MAX_N*MAX_N][MAX_N*MAX_N];    //状态转移概率矩阵
char A[4] = { 'n','e','s','w' };     //Action ,'↑','→','↓','←'
int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };  //四向移动
int r = -1;                  //奖励值
float disc = 1.0f;            //折扣值
float en = 0.0000001f;        //sub小于这个数时收敛

 //初始化							  
void init() {
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++) {
			S[i][j] = 'w';                    //初始化为向右走
		}
	S[0][2] = '#';                       //#障碍
	S[3][1] = 'E';                       //E目标点			
	S[2][2] = '#';
	S[1][2] = 'E';
	S[1][2] = '#';
}


int getIndex(char ch) {
	switch (ch) {
	case 'n':
		return 0;
	case 'e':
		return 1;
	case 's':
		return 2;
	case 'w':
		return 3;
	default:
		return -1;
	}
}

void printVal() {
	puts("----------------value-----------------");
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			printf("%.4f ", V[i][j]);
		}
		puts("\n");
	}
}

void ValueIteration() {
	float sub = 0;
	int cnt = 0;
	do {
		sub = 0;
		for (int i = 0; i < MAX_N; i++) {
			for (int j = 0; j < MAX_N; j++) {
				if (S[i][j] != '#' && S[i][j] != 'E') {           //不是障碍物及终点
					float val = V[i][j];
					int k = 4;
					int ma = INF;
					while (k--) {
						int x = i + dx[k], y = j + dy[k];
						if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && S[x][y] != '#') {
							float round = r + disc * OLDV[x][y];
							if (ma < round) {
								 ma = round;    //改变Val值
							}
						}
					}
					if (ma != INF)
						V[i][j] = ma;                        //V[i][j]取得周围环境的最大值

					sub = max(sub, fabs(val - V[i][j]));
				}
			}
		}

		//把新的val值拷贝到旧的数组中
		for (int i = 0; i < MAX_N; i++) {
			for (int j = 0; j < MAX_N; j++) {
				OLDV[i][j] = V[i][j];
			}
		}
		printf("cnt :   %d\n", ++cnt);
		printVal();

	} while (sub >= en);


	//更新最佳策略
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			if (S[i][j] != '#' && S[i][j] != 'E') {           //不是障碍物及终点
				int k = 4;
				int ma = INF;
				while (k--) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && S[x][y] != '#') {
						float round = r + disc * OLDV[x][y];
						if (ma < round) {
							ma = round;    //改变Val值
							S[i][j] = A[k];
						}
					}
				}
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA); //亮绿
	//打印策略
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			char ch;
			switch (S[i][j]) {
			  case 'n':
				  printf("↑ ");
				  break;
			  case 'e':
				  printf("→ ");
				  break;
			  case 's':
				  printf("↓ ");
				  break;
			  case 'w':
				  printf("← ");
				  break;
			  default:
				  printf("%c ", S[i][j]);
				  break;
			}
		}
		puts("\n");
	}

}


int main() {

	init();
	ValueIteration();
	return 0;
}