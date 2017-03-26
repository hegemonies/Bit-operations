#include <stdio.h>
#include "coder.h"
#include "command.h"

int main(int argc, char *argv[])
{
	/*
	if (*argv[] == "coder")
		coder();
	*/
	int i;
	for (i = 0; i < argc; ++i) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	return 0;
}