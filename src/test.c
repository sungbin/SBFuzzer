#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("TEST START!\n");
	if(argc != 1) {
		printf("ERROR: the number of input must be one\r\n");
		return 1;
	}
	printf("Say Hello!\r\n");
	return 0;
}
