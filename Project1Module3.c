#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


// Instruction Codes

#define ADD_operation 1
#define SUB_operation 2
#define LOAD_operation 3
#define STORE_operation 4

// Registers and Memory Arrays
int dataMemory[100];
int memory[] = {333, 122, 120, 215, 205};
int PC;
int ACC;
int IR;
int statusRegister;

// void -> void
// set all data memory elements to 0;
void initialize_dataMemory() {
	for (int i=0; i < sizeof(dataMemory); i++) {
		dataMemory[i] = i;
	}
}

// void -> int
// Fetch Instructions from memory
int fetchInstruction() {
	return memory[PC];
}

// int -> int
// Get the address of the instruction
int get_address(int n) {
	int temp = 0;
	int factor = 1;

	while (n / 10 != 0) {
		int m = n % 10;
		n /= 10;
		temp += factor * m;
		factor *= 10;
	}
	return temp;
}

// int -> int
// Get the opcode of the instruction
int get_opcode(int instruction) {
	int first = instruction;
	while (first >= 10) {
		first = first / 10;
	}
	return first;
}

// execute based on operation code
void executeInstruction(int instruction) {
	int opcode = get_opcode(instruction);
	int address = get_address(instruction);
	int prev;

	switch(opcode) {
		case ADD_operation:
			// perform addition
			prev = ACC;
			ACC = prev + dataMemory[address];
			printf("Adding: %d + %d = %d\n", prev, dataMemory[address], ACC);
			break;
		case SUB_operation:
			// perform substraction
			prev = ACC;
			ACC = prev - dataMemory[address];
			printf("Subtracting: %d - %d = %d\n", prev, dataMemory[address], ACC);
			break;
		case LOAD_operation:
			// perform loading
			ACC = dataMemory[address];
			printf("Loading data in ACC: %d -> %d\n", dataMemory[address], ACC);
			break;
		case STORE_operation:
			// perform storing
			dataMemory[address] = ACC;
			printf("Storing data into memory from ACC: %d -> %d\n", ACC, dataMemory[address]);
			break;
		default:
			// Handle undefined/invalid opcodes
			printf("Invalid opcode given. Please try again.\n");
			break;
		}
}

int main() {
	initialize_dataMemory();
	PC = 0;
	while (PC < sizeof(memory) / sizeof(memory[0])) {
		IR = fetchInstruction();
		PC++;
		executeInstruction(IR);
	}
	return 0;
}
