#include <stdio.h>
#include "coder.h"
#include "command.h"

void print_code_unit(CodeUnit code_unit)
{
	printf("bin code:\n");
	int num_bait = 1;
	while (num_bait <= code_unit.length) {
		for (int j = 8; j > 0; j--) {
			printf("%d", (code_unit.code[num_bait - 1] >> (j - 1)) & 1);
		}
		num_bait++;
		printf(" ");
	}
	printf("\nlength: %x\n", code_unit.length);
}

int main(int argc, char *argv[])
{
	/*
	if (*argv[] == "coder")
		coder();
	*/
	//int i;
	// for (i = 0; i < argc; ++i) {
	//	printf("argv[%d] = %s\n", i, argv[i]);
	//}
	CodeUnit code_unit;
	encode(128, &code_unit);
	print_code_unit(code_unit);
	printf("%" PRIx32 "\n", decode(&code_unit));
	
	return 0;
}