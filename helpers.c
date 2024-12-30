#include <stdio.h>
#include <string.h>
#include "helpers.h"

int get_bits(int num, int start, int end) {
   int width_mask = (1 << (end - start + 1)) - 1;
   int positioned_mask = width_mask << start;
   int masked = num & positioned_mask;
   return masked >> start;
}

void get_mod(char *mod, char *encoding){
	snprintf(mod, 3, "%d%d", encoding[0], encoding[1]);
}

void get_r_m(char *r_m, char *encoding) {
	snprintf(r_m, 3, "%d%d%d", encoding[2], encoding[3], encoding[4]);
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


char *reg_to_string(int reg) {
	switch (reg) {
		case 0:
			return "ax";
		case 1:
			return "cx";
		case 2:
			return "dx";
		case 3:
			return "bx";
		case 4:
			return "sp";
		case 5:
			return "bp";
		case 6:
			return "si";
		case 7:
			return "di";
		default:
			return "ILLEGAL_REG";
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
