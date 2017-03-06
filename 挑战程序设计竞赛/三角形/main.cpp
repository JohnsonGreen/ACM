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

    //sort比qsort快一些
    sort(a, a+n);

    for(int i = n - 1; i > 1;i--){
        for(int j = i - 1; j > 0;j--){
            for(int k = j - 1; k >=0; k--){
                if(a[i] < a[j] + a[k]){
                   printf("%d\n",a[i]+a[j]+a[k]);

                   goto last;          //跳出三重循环，此处使用goto非常方便，但是不能滥用
                }
        }
     }
   }

    printf("%d---不能组成三角形",0);

    last:
        return 0;


}
