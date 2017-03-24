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
	} else if (count <= 11) {
		
		//code_units->code[0] = code_point & 0xDF;
		
		code_units->code[1] = ((code_point << 5) >> 5) | 0x80;
		code_units->lenght = 2;
	} else if (count <= 16) {
		code_units->code[0] = code_point & ;
		code_units->lenght = 3;
	} elese if (count <= 21) {
		code_units->code[0] = code_point & ;
		code_units->lenght = 4;
	}
}
/*
uint32_t decode(const CodeUnit *code_unit)
{

}

int read_next_code_unit(FILE *in, CodeUnits *code_units)
{

}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{

}
*/
