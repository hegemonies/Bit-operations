#include <stdio.h>
#include <string.h>
#include "coder.h"
#include "command.h"

int main(int argc, char *argv[])
{
	
	if (argc != 4) {
		printf("Usage:\n"
		"coder encode <in-file-name> <out-file-name>\n"
		"coder decode <in-file-name> <out-file-name>\n");
		return -1;
	}
	
	if(!strcmp(argv[1], "decode")) {
		if (decode_file(argv[2], argv[3])) {
			printf("Error decode file\n");
			return -1;
		} 
	} else if(!strcmp(argv[1], "encode")) {
		if (encode_file(argv[2], argv[3])) {
			printf("Error encode file\n");
			return -1;
		} 
	} else {
		printf("Usage:\n"
		"coder encode <in-file-name> <out-file-name>\n"
		"coder decode <in-file-name> <out-file-name>\n");
	}
	
	/*
	CodeUnit code_unit;
	encode(128, &code_unit);
	print_code_unit(code_unit);
	printf("%" PRIx32 "\n", decode(&code_unit));
	*/
	return 0;
}