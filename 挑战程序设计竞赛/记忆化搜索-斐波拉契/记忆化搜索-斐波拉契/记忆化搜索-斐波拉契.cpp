#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>


const int MAX_N = 2 << 10;

int mem[MAX_N];

int fib(int n) {
	if (n <= 1)
		return n;
	if (mem[n] != 0)
		return mem[n];
	
	return mem[n] = fib(n - 1) + fib(n - 2);

}

int main() {


	int n;
	scanf_s("%d", &n);

	
	for (int i = 0; i <= n; i++) {
		printf("%d, ", fib(i));
	}

	return 0;

}

