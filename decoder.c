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
		int dw = get_bits(bin_buffer[pos], 0, 2);
		char *op_string = op_code_to_string(op_code);
		strcat(output_buf, op_string);
		/*printf("%d\n", dw);*/

		instruction_t instr = op_code_to_instr(op_code);
		switch(instr){
			case MOV:{
				int mod = get_bits(bin_buffer[pos+1], 6, 7);
				int reg_m = get_bits(bin_buffer[pos+1], 3, 5);
				int reg = get_bits(bin_buffer[pos+1], 0, 2);
				/*printf("%d\n", mod);*/
				/*printf("%s\n", reg_to_string(reg_m));*/
				/*printf("%s\n", reg_to_string(reg));*/
				strcat(output_buf, " ");
				strcat(output_buf, reg_to_string(reg_m));
				strcat(output_buf, ", ");
				strcat(output_buf, reg_to_string(reg));
				pos++;
			}
		}
		printf("%s\n", output_buf);
		pos++;
	}
}

