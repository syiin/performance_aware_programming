#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

void parse_instruction(decoder_t *decoder, char *output_buf){
	strcat(output_buf, format_op(decoder));
	char byte_str[9];
	byte_to_binary(decoder->bin_buffer[decoder->pos], byte_str);
	/*printf("BYTE: %s\n", byte_str);*/
	/*printf("OPCODE: %d\n", decoder->opcode);*/
	switch(decoder->opcode){
		case 34:{
			int reg = slice_peek_bits(decoder, 0, 2);
			int reg_m = slice_peek_bits(decoder, 3, 5);

			strcat(output_buf, " ");
			strcat(output_buf, reg_to_string(reg, decoder->w_bit));
			strcat(output_buf, ", ");
			strcat(output_buf, reg_to_string(reg_m, decoder->w_bit));

			decoder->pos++;
		}
	}
	decoder->pos++;
}

char *format_op(decoder_t *decoder){
	return op_code_to_string(decoder->opcode);
}

void set_op_code(decoder_t *decoder){
	uint8_t byte = decoder->bin_buffer[decoder->pos];
	/*decoder->opcode = byte & 0xFC;*/
	decoder->opcode = byte >> 2;
	decoder->d_bit = byte & 0x1;
	decoder->w_bit = byte & 0x1;
}

void set_modrm(decoder_t *decoder){
	uint8_t byte = decoder->bin_buffer[decoder->pos+1];
	decoder->mod = byte >> 6;
	decoder->regm = (byte >> 3) & 0x7;
	decoder->reg = byte & 0x7;
}

int slice_current_bits(decoder_t *decoder, int start, int end){
	return get_bits(decoder->bin_buffer[decoder->pos], start, end);
}

int slice_peek_bits(decoder_t *decoder, int start, int end){
	return get_bits(decoder->bin_buffer[decoder->pos+1], start, end);
}

int get_bits(int num, int start, int end) {
   int width_mask = (1 << (end - start + 1)) - 1;
   int positioned_mask = width_mask << start;
   int masked = num & positioned_mask;
   return masked >> start;
}

char *r_m_to_register(char *op_code){
	if (strcmp(op_code, "011")) return "BX";
	if (strcmp(op_code, "001")) return "CX";
	return "ILLEGAL OP";
}

void get_reg(char *reg, char *encoding) {
	snprintf(reg, 3, "%d%d%d", encoding[5], encoding[6], encoding[7]);
}

byte_t *read_binary_file(const char *file_path, size_t *bin_size){
	FILE *file = fopen(file_path, "rb");
	if (!file){
		return NULL;
	}
	// Get the size of the file - may be inefficient as files get larger
	fseek(file, 0, SEEK_END);
	*bin_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	byte_t *bin_buffer = malloc(*bin_size);
	if (!bin_buffer){
		fclose(file);
		return NULL;
	}

	fread(bin_buffer, sizeof(byte_t), *bin_size, file);
	fclose(file);

	return bin_buffer;
}

void byte_to_binary(uint8_t byte, char* binary) {
    for(int i = 7; i >= 0; i--) {
        binary[7-i] = (byte & (1 << i)) ? '1' : '0';
    }
    binary[8] = '\0';
}

instruction_t op_code_to_instr(int op_code){
	switch (op_code){
		case (34):
			return MOV;
		default:
			return MOV;
	}
}

char *op_code_to_string(int op_code){
	switch (op_code){
		case (34):
			return "mov";
		default:
			return "ILLEGAL OP";
	}
}

reg_t reg_encoding_to_register(int reg_encoding){
	switch (reg_encoding){
		case (1):
			return CX;
		case (3):
			return BX;
		default:
			return ILLEGAL_REG;
	}
}


char *reg_to_string(int reg, int is_16_bit) {
	switch (reg) {
		case 0: return is_16_bit ? "ax" : "al";
		case 1: return is_16_bit ? "cx" : "cl";
		case 2: return is_16_bit ? "dx" : "dl";
		case 3: return is_16_bit ? "bx" : "bl";
		case 4: return is_16_bit ? "sp" : "ah";
		case 5: return is_16_bit ? "bp" : "ch";
		case 6: return is_16_bit ? "si" : "dh";
		case 7: return is_16_bit ? "di" : "bh";
		default: return "ILLEGAL_REG";
	}
}

void print_encoding_to_int(char *encoding){
	printf("%d\n", (int)strtol(encoding, NULL, 2));
}

void print_position(byte_t *buffer, int pos){
	char bin_string[9];
	byte_to_binary(buffer[pos], bin_string);
	printf("%s\n", bin_string);
}
