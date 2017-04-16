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
float V[MAX_N][MAX_N];      //ֵ����
float OLDV[MAX_N][MAX_N];    //����ɵ�valֵ
char S[MAX_N][MAX_N];      //״̬����ֱ�۴洢�˶�����
char OLDS[MAX_N][MAX_N];   //�ɵ�״̬����
char A[4] = { 'n','e','s','w' };     //Action ,'��','��','��','��'
int dx[] = { -1,0,1,0 }, dy[]= { 0,1,0,-1 };  //�����ƶ�
int r = -1;                  //����ֵ
float disc = 0.5f;            //�ۿ�ֵ
float en = 0.00000001f;        //subС�������ʱ����


//  ��ȡ������ľ��
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

//��ʼ��
void init() {
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++) {
			S[i][j] = 'n';                    //��ʼ��Ϊ������
			OLDS[i][j] = 'n';
		}
	//  OLDS[0][0] = S[0][0] = '#';                       
	  OLDS[3][3] = S[3][3] = 'E';                       //Ŀ���	
	 // OLDS[2][2] = S[2][2] = '#';      //�ϰ�
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
	//��ӡ����
	for (int i = 0; i < MAX_N; i++) {
		printf("        ");
		for (int j = 0; j < MAX_N; j++) {
			switch (S[i][j]) {
			case 'n':
				printf("��  ");
				break;
			case 'e':
				printf("��  ");
				break;
			case 's':
				printf("��  ");
				break;
			case 'w':
				printf("��  ");
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

				if (S[i][j] != '#' && S[i][j] != 'E') {           //�����ϰ��Ｐ�յ�
					float val = V[i][j];
					int k = getIndex(S[i][j]);       //����״̬�ó��ƶ��±�
					int x = i + dx[k], y = j + dy[k];
					if (x >= 0 && x < MAX_N && y >= 0 && y < MAX_N && S[x][y] != '#') {
						V[i][j] = r +  disc * OLDV[x][y];
					}
					sub = max(sub, fabs(val - V[i][j]));
				}
			}
	   }

		//���µ�valֵ�������ɵ�������
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
							ma = round;    //�ı�Valֵ
							S[i][j] = A[k];    //�ı䵱ǰ״̬����Ѳ���
							char ch = A[k];
						}
					}
				}

				if (oldact != S[i][j])
					stable = false;
			}
		}
	}

	//��������״̬��������״̬
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			OLDS[i][j] = S[i][j];
		}
	}
		
	if (stable) {
	   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	   printf("\n--------------------------STOP-----------------------\n");

	   printVal();
	   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA); //����
	   printState();
	   break;
	 }
	 else {
	    PolicyEvaluation();    //�������Ե���
     }
   }
}

int main() {

	init();
	PolicyEvaluation();
	PolicyImprovement();
	return 0;
}
