#include <stdio.h>
#include <inttypes.h>
#include "coder.h"

int encode(uint32_t code_point, CodeUnits *code_units);
{
	uint8_t count = 0;
	for (uint32_t i = code_point; i > 0; i >> 1) {
		count++;
	}
	if (count <= 7) {
		code_units->code[0] = code_point;
		code_units->lenght = 1;
		return 0;
	} else if (count <= 11) {
		code_units->code[0] = (code_point >> 6) | 0xC0;
		code_units->code[1] = (code_point & 0x3F) | 0x80;
		code_units->lenght = 2;
		return 0;
	} else if (count <= 16) {
		code_units->code[0] = (code_point >> 12) | 0xE0;
		code_units->code[1] = ((code_point & 0xFC0) >> 6) | 0x80;
		code_units->code[2] = (code_point & 0x3F) | 0x80;
		code_units->lenght = 3;
		return 0;
	} else if (count <= 21) {
		code_units->code[0] = (code_point >> 18) | 0xF0;
		code_units->code[1] = (code_point & 0x3F000) >> 12;
		code_units->code[2] = (code_point & 0xFC0) >> 6;
		code_units->code[3] = code_point & 0x3F;
		code_units->lenght = 4;
		return 0;
	}
	return -1;
}

uint32_t decode(const CodeUnit *code_unit)
{

}
/*
int read_next_code_unit(FILE *in, CodeUnits *code_units)
{

}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{

}
*/