#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <queue>
#include <windows.h>  
#include <string>

using namespace std;

const int MAX_N = 4;
const float INF = -999999999.0f;
float V[MAX_N][MAX_N];      //值矩阵
float OLDV[MAX_N][MAX_N];    //保存旧的val值
char S[MAX_N][MAX_N];      //状态矩阵，直观存储运动方向
char OLDS[MAX_N][MAX_N];   //旧的状态矩阵
char A[4] = { 'n','e','s','w' };     //Action ,'↑','→','↓','←'
int dx[] = { -1,0,1,0 }, dy[]= { 0,1,0,-1 };  //四向移动
int r = -1;                  //奖励值
float disc = 0.5f;            //折扣值
float en = 0.00000001f;        //sub小于这个数时收敛


//  获取输出流的句柄
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

//初始化
void init() {
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++) {
			S[i][j] = 'n';                    //初始化为向右走
			OLDS[i][j] = 'n';
		}
	//  OLDS[0][0] = S[0][0] = '#';                       
	  OLDS[3][3] = S[3][3] = 'E';                       //目标点	
	 // OLDS[2][2] = S[2][2] = '#';      //障碍
	//  OLDS[2][1] = S[2][1] = '#';
	 // OLDS[2][3] = S[2][3] = '#';

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
			printf("%f ", V[i][j]);
		}
		puts("\n");
	}
}
void printState() {
	puts("----------------State-----------------");
	//打印策略
	for (int i = 0; i < MAX_N; i++) {
		printf("        ");
		for (int j = 0; j < MAX_N; j++) {
			switch (S[i][j]) {
			case 'n':
				printf("↑  ");
				break;
			case 'e':
				printf("→  ");
				break;
			case 's':
				printf("↓  ");
				break;
			case 'w':
				printf("←  ");
				break;
			default:
				printf("%c   ", S[i][j]);
				break;
			}
		}
		puts("\n");
	}
}

void PolicyEvaluation(){
	float sub;
	int cnt = 0;
	do{
		sub = 0.0f;
		for (int i = 0; i < MAX_N; i++) {
			for (int j = 0; j < MAX_N; j++) {

				if (S[i][j] != '#' && S[i][j] != 'E') {           //不是障碍物及终点
					float val = V[i][j];
					int k = getIndex(S[i][j]);       //根据状态得出移动下标
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && S[x][y] != '#') {
						V[i][j] = r +  disc * OLDV[x][y];
					}
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
			
	} while (sub > en);
}

void PolicyImprovement() {

  while (true) {

	bool stable = true;
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			if (OLDS[i][j] != '#' && OLDS[i][j] != 'E') {
				char oldact = OLDS[i][j];
				int k = 4;
				float ma = INF;
				while (k--) {
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && OLDS[x][y] != '#') {
						float round = r + disc * OLDV[x][y];
						if (round - ma > en) {
							ma = round;    //改变Val值
							S[i][j] = A[k];    //改变当前状态的最佳策略
							char ch = A[k];
						}
					}
				}

				if (oldact != S[i][j])
					stable = false;
			}
		}
	}

	//将所有新状态拷贝至旧状态
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			OLDS[i][j] = S[i][j];
		}
	}
		
	if (stable) {
	   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	   printf("\n--------------------------STOP-----------------------\n");

	   printVal();
	   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA); //亮绿
	   printState();
	   break;
	 }
	 else {
	    PolicyEvaluation();    //继续策略迭代
     }
   }
}

int main() {

	init();
	PolicyEvaluation();
	PolicyImprovement();
	return 0;
}
