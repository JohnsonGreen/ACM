#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int n,a[101];
    scanf("%d",&n);

    for(int i = 0;i < n;i++){
        scanf("%d", &a[i]);
    }

    //sort��qsort��һЩ
    sort(a, a+n);

    for(int i = n - 1; i > 1;i--){
        for(int j = i - 1; j > 0;j--){
            for(int k = j - 1; k >=0; k--){
                if(a[i] < a[j] + a[k]){
                   printf("%d\n",a[i]+a[j]+a[k]);

                   goto last;          //��������ѭ�����˴�ʹ��goto�ǳ����㣬���ǲ�������
                }
        }
     }
   }

    printf("%d---�������������",0);

    last:
        return 0;


}
