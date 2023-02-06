#include <stdio.h>

int main() {
	int n = 1;
	int sum = 0;

	while (n <= 100) {
		sum += n;
		n++;
	}

	printf("%d\n", sum);
	return 0;
}