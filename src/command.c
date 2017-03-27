#include <stdio.h>
#include <inttypes.h>
#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");
	if (in == NULL) {
		return -1;
	}
	CodeUnit unit;
	/*
	for (int i = 0; i != EOF; i++) {
		uint32_t a;
		fscanf(in, "%x", &a);
		encode(a, &unit);
	}
	*/
	uint32_t a;
	while(fscanf(in, "%x", &a) != EOF) {
		uint32_t a = 0;
		encode(a, &unit);
	}
	fclose(in);
	FILE *out = fopen(out_file_name, "w");
	if (out == NULL) {
		return -1;
	}
	fwrite(&(unit.code), unit.length, MaxCodeLength, out);
	fclose(out);
	return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");
	if (in == NULL) {
		return -1;
	}
	CodeUnit unit;
	uint32_t a;
	while(fscanf(in, "%x", &a) != EOF) {
		decode(&unit);
	}
	fclose(in);
	FILE *out = fopen(out_file_name, "w");
	if (out == NULL) {
		return -1;
	}
	fwrite(&(unit.code), unit.length, MaxCodeLength, out);
	fclose(out);
	return 0;
}