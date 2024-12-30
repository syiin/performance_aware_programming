#include <string.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <file_path>\n", argv[0]);
		return 1;
	}

	// Get the file path from the arguments
	const char *file_path = argv[1];
	size_t bin_size;
	byte_t *bin_buffer = read_binary_file(file_path, &bin_size);
	if (!bin_buffer){
		return 0;
	}

	size_t pos = 0;
	char output_buf[128];
	while (pos < bin_size){
		strcpy(output_buf, "");

		//HANDLE OP BYTE
		int op_code = get_bits(bin_buffer[pos], 2, 7);
		int d_bit = get_bits(bin_buffer[pos], 1, 1);
		int w_bit = get_bits(bin_buffer[pos], 0, 0);
		char *op_string = op_code_to_string(op_code);
		strcat(output_buf, op_string);

		instruction_t instr = op_code_to_instr(op_code);
		switch(instr){
			case MOV:{
				int mod = get_bits(bin_buffer[pos+1], 6, 7);
				//REGISTER TO REGISTER MOVEMENT
				if (mod == 3){
					int reg = get_bits(bin_buffer[pos+1], 0, 2);
					int reg_m = get_bits(bin_buffer[pos+1], 3, 5);

					strcat(output_buf, " ");
					strcat(output_buf, reg_to_string(reg, w_bit));

					strcat(output_buf, ", ");
					strcat(output_buf, reg_to_string(reg_m, w_bit));
					pos++;
				}
			}
		}
		printf("%s\n", output_buf);
		pos++;
	}
}

