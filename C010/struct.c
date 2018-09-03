#include <stdio.h>

int main() {
	struct student {
		char *firstName;
		char *surName;
		int age;
		int height;
	};
	
	struct student S1, S2[3], *S3;

	S1.firstName = "Afet";
	S1.surName = "Shehvet";
	S1.age = 999;
	scanf("%d", &S1.height);

	printf("%s", S1.firstName);

	printf("\n");
	return 0;
}
