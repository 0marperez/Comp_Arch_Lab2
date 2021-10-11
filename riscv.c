#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <stdint.h> 
#include "tokenizer.h" 
#include "memory.h" 

int32_t* reg; 
void init_regs();
bool interpret(char* instr);
void write_read_demo();

/*
 * Initialize register array for usage.
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

/*
 * Prints registers
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/*
 * Checks if two strings are equal
 */
bool compare_strings(char* str1, char* str2){
	int i = 0;
	int j = 0;
	while(str1[i] != '\0' || str2[j] != '\0'){
		if(str1[i] != str2[j]) return false;
		if(str1[i] != '\0') ++i;
		if(str2[j] != '\0') ++j;

	}
	if(j != i) return false;
	return true;
} 

/*
 * Determines what kind of instruction we're given
 */
int find_type(char* instruction){
	if(compare_strings(instruction, "LW")) return 0;
	if(compare_strings(instruction, "SW")) return 1;
	if(compare_strings(instruction, "ADD")) return 2;
	if(compare_strings(instruction, "ADDI")) return 3;
	if(compare_strings(instruction, "AND")) return 4;
	if(compare_strings(instruction, "OR")) return 5;
	if(compare_strings(instruction, "XOR")) return 6;
	return -1;
}

/*
 * Converts decimal number to hex
 */
int32_t to_hex(int decimal){
	char hexstring[32]; 
    sprintf(hexstring, "0x%08x", decimal); 
	return (int32_t)strtol(hexstring, NULL, 16);
}

/*
 * Interprets user input to execute RV64 instructions.
 */
bool interpret(char* instr){
	int num_tokens = count_tokens(instr);
    char** tokens = get_tokens(instr, num_tokens);
	int type = find_type(tokens[0]);

	switch(type){
		//LW
		case 0:
		{
			tokens[1]++;
			tokens[3]++;	
			int32_t mem_address = atoi(tokens[2]) + reg[atoi(tokens[3])];
			int32_t read_data = read_address(to_hex(mem_address), "mem.txt");
			reg[atoi(tokens[1])] = read_data;
			tokens[1]--;
			tokens[3]--;	
			break;
		} 
		//SW
		case 1:
		{
			tokens[1]++;
			tokens[3]++;	
			int32_t mem_address = atoi(tokens[2]) + reg[atoi(tokens[3])]; 
			write_address(reg[atoi(tokens[1])], to_hex(mem_address), "mem.txt");
			tokens[1]--;
			tokens[3]--;	
			break;			
		}
		//ADD
		case 2: 
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];
			tokens[1]--;
			tokens[2]--;
			tokens[3]--;	
			break;
		//ADDI
		case 3:
			tokens[1]++;
			tokens[2]++;		
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] + reg[atoi(tokens[3])];
			tokens[1]--;
			tokens[2]--;
			break;
		//AND
		case 4:
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] & reg[atoi(tokens[3])];
			tokens[1]--;
			tokens[2]--;
			tokens[3]--;
			break;
		//OR
		case 5:
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] | reg[atoi(tokens[3])];
			tokens[1]--;
			tokens[2]--;
			tokens[3]--;
			break;
		//XOR
		case 6:
			tokens[1]++;
			tokens[2]++;
			tokens[3]++;			
			reg[atoi(tokens[1])] = reg[atoi(tokens[2])] ^ reg[atoi(tokens[3])];
			tokens[1]--;
			tokens[2]--;
			tokens[3]--;		
			break;
		//ERROR
		case -1:
			printf("Did not enter a correct instruction");
			break;
	}

	print_regs();
}

/**
 * Your code goes in the main
 */
int main(){
	char* instruction = malloc(100 * sizeof(char));
	bool is_null = false;

	init_regs();

	//Getting instructions & interpreting them
	while(!is_null){
		printf("Please enter the input string ('ctr + d' to exit) ");
		is_null = fgets(instruction, 100, stdin) == NULL;
		if(!is_null) interpret(instruction);
	}
    return(0);
}
