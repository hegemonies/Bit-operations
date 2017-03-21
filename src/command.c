#include <stdio.h>
#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");
	if (in == NULL)
		return -1
	FILE *out = fopen(out_file_name, "w");
	if (out == NULL)
		return -1;
	unsigned int a[sizeof(code)];
	fscanf(in, "%x ", a);
	
	encode();
	
	fwrite(a, sizeof(code), MaxCodeLength, OUT);
	fclose(in);
	fclose(out);
	return 0;
}
