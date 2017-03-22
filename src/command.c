#include <stdio.h>
#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");
	if (in == NULL) {
		return -1;
	}
	FILE *out = fopen(out_file_name, "w");
	if (out == NULL) {
		return -1;
	}
	CodeUnits *unit;
	for (int i = 0; i != EOF; i++) {
		uint32_t a;
		fscanf(in, "%x ", a);
		encode(a, &unit);
	}
	
	encode();
	
	fwrite(a, sizeof(code), MaxCodeLength, OUT);
	fclose(in);
	fclose(out);
	return 0;
}
