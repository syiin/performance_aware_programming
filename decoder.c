#include <stdio.h>

int main(){
	FILE *fptr = fopen("listings/listing_37", "rb");
	char asm_buffer[256];
	fgets(asm_buffer, 100, fptr);
	printf("%s\n", asm_buffer);
	return 0;
}
