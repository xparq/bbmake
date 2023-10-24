#include <stdio.h>

extern int x;
const char* subname();

int main()
{
	printf("hi, with %d, and also from %s\n", x, subname());
	return 0;
}
