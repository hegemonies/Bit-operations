#include <stdio.h>
#include <inttypes.h>
#include "coder.h"

int encode(uint32_t code_point, CodeUnit *code_units)
{
	uint8_t count = 0;
	for (uint32_t i = code_point; i > 0; i >>= 1) {
		count++;
	}
	if (count <= 7) {
		code_units->code[0] = code_point;
		code_units->length = 1;
		return 0;
	} else if (count <= 11) {
		code_units->code[0] = (code_point >> 6) | 0xC0;
		code_units->code[1] = (code_point & 0x3F) | 0x80;
		code_units->length = 2;
		return 0;
	} else if (count <= 16) {
		code_units->code[0] = (code_point >> 12) | 0xE0;
		code_units->code[1] = ((code_point & 0xFC0) >> 6) | 0x80;
		code_units->code[2] = (code_point & 0x3F) | 0x80;
		code_units->length = 3;
		return 0;
	} else if (count <= 21) {
		code_units->code[0] = (code_point >> 18) | 0xF0;
		code_units->code[1] = (code_point & 0x3F000) >> 12;
		code_units->code[2] = (code_point & 0xFC0) >> 6;
		code_units->code[3] = code_point & 0x3F;
		code_units->length = 4;
		return 0;
	}
	return -1;
}

uint32_t decode(const CodeUnit *code_unit)
{
	uint32_t code_point;
	if ((code_unit->code[0] >> 7) == 0) {
		return (code_point = code_unit->code[0]);
	} else if (code_unit->code[0] <= 0xDF) {
			return (code_point = (((code_unit->code[0] & 0x1F) << 6) | (code_unit->code[1] & 0x3F)));
	} else if (code_unit->code[0] <= 0xEF) {
			return (((code_unit->code[0] & 0xF) << 12) | ((code_unit->code[1] & 0x3F) << 6) | (code_unit->code[2] & 0x3F));
	} else if (code_unit->code[0] <= 0xF7) {
			return (((code_unit->code[0] & 0x7) << 18) | ((code_unit->code[1] & 0x3F) << 12) | ((code_unit->code[2] & 0x3F) << 6) | (code_unit->code[3] & 0x3F));
	}
	return 0;
}
/*
int read_next_code_unit(FILE *in, CodeUnit *code_units)
{

}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{

}
*/