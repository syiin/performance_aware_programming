#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int main(){
	size_t bin_size;
	byte_t *bin_buffer = read_binary_file("listings/listing_37", &bin_size);
	if (!bin_buffer){
		return 0;
	}

	size_t pos = 0;
	while (pos < bin_size){
		//HANDLE OP BYTE
		int op_code = get_bits(bin_buffer[pos], 2, 7);
		int dw = get_bits(bin_buffer[pos], 0, 2);
		char *op_string = op_code_to_string(op_code);
		printf("%s\n", op_string);
		printf("%d\n", dw);
		instruction_t instr = op_code_to_instr(op_code);

		/*char bin_string[9];*/
		/*byte_to_binary(bin_buffer[pos], bin_string);*/
		/*printf("%s\n", bin_string);*/
		if (instr == MOV){
			int mod = get_bits(bin_buffer[pos+1], 6, 7);
			int reg_m = get_bits(bin_buffer[pos+1], 3, 5);
			int reg = get_bits(bin_buffer[pos+1], 0, 2);
			printf("%d\n", mod);
			printf("%s\n", reg_to_string(reg_m));
			printf("%s\n", reg_to_string(reg));

			char bin_string[9];
			byte_to_binary(bin_buffer[pos+1], bin_string);
			printf("%s\n", bin_string);
			pos++;

		}
		pos++;
	}
}

