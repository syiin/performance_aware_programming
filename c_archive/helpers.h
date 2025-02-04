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
	ILLEGAL_REG,
} reg_t;

typedef struct CurrentBits{
	uint8_t opcode;
	uint8_t modrm;
} current_bits_t;

typedef struct Decoder {
	size_t pos;
	uint8_t opcode;
	uint8_t d_bit;
	uint8_t w_bit;
	uint8_t mod;
	uint8_t regm;
	uint8_t reg;
	const byte_t *bin_buffer;
} decoder_t;

void parse_instruction(decoder_t *decoder, char *output_buf);
char *format_op(decoder_t *decoder);
void set_op_code(decoder_t *decoder);
void set_modrm(decoder_t *decoder);

int slice_current_bits(decoder_t *decoder, int start, int end);
int slice_peek_bits(decoder_t *decoder, int start, int end);
int get_bits(int num, int start, int end);
void get_reg(char *reg, char *encoding);
byte_t *read_binary_file(const char *file_path, size_t *bin_size);
void byte_to_binary(uint8_t byte, char* binary);
instruction_t op_code_to_instr(int op_code);
char *op_code_to_string(int op_code);
void print_encoding_to_int(char *encoding);
char *reg_to_string(int reg, int is_16_bit);

#endif
