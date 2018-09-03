#include <stdio.h>

int main() {
	int a, b, result, binary[32];
	char oper;
	scanf("%c%d%d", &oper, &a, &b);
	switch (oper) {
		case '|': 
			result = a|b;
			break;
		case '&':
			result = a&b;
			break;
		case '^':
			result = a^b;
			break;
	}
	for (int i = 31; i >= 0; i--) {
		binary[i] = result % 2;
		result /= 2;
	}
	for (int i = 0; i < 32; i++) printf("%d", binary[i]);
	printf("\n");
}
