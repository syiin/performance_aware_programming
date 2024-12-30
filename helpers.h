#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t byte_t;

typedef enum {
	MOV,
} instruction_t;

typedef enum {
	CX,
	BX,
	ILLEGAL_REG
} reg_t;

typedef struct {
	size_t pos;
	const byte_t *bin_buffer;
} decoder_t;


int get_bits(int num, int start, int end);
void get_mod(char *mod, char *encoding);
void get_r_m(char *r_m, char *encoding);
void get_reg(char *reg, char *encoding);
byte_t *read_binary_file(const char *file_path, size_t *bin_size);
void byte_to_binary(uint8_t byte, char* binary);
instruction_t op_code_to_instr(int op_code);
char *op_code_to_string(int op_code);
void print_encoding_to_int(char *encoding);
char *reg_to_string(int reg);

#endif
