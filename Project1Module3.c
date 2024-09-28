#include <stdio.h>
// Instruction Codes

#define ADD_operation 1
#define SUB_operation 2
#define LOAD_operation 3
#define STORE_operation 4

// Registers and Memory Arrays
int registerAdd = 0;
int registerSub = 0;
int registerLoad = 0;
int memory[100];


// execute based on operation code
void executeInstruction(int opcode, int operand1, int operand2) {
	switch(opcode) {
		case ADD_operation:
			// perform addition
			registerAdd = operand1 + operand2;
			printf("Adding: %d + %d = %d\n", operand1, operand2, registerAdd);
			break;
		case SUB_operation:
			// perform substraction
			registerSub = operand1 - operand2;
			printf("Subtracting: %d - %d = %d\n", operand1, operand2, registerSub);
			break;
		case LOAD_operation:
			// perform loading
			if (operand1 >= 0 && operand1 <= 100) {
				registerLoad = memory[operand1];
			} else {
				printf("Invalid operand1 value. Please keep operand1 between 0 and 100.\n");
			}
			break;
		case STORE_operation:
			// perform storing
			if (operand1 >= 0 && operand1 <= 100) {
				memory[operand1] = registerLoad;
			} else {
				printf("Invalid operand1 value. Please keep operand1 between 0 and 100.\n");
			}
			break;
		default:
			// Handle undefined/invalid opcodes
			printf("Invalid opcode given. Please try again.\n");
			break;
		}
}

int main() {
	memory[23] = 17;
	executeInstruction(1, 10, 5);
	printf("10 + 5 = %d\n", registerAdd);

	executeInstruction(2, 10, 7);
	printf("10 - 7 = %d\n", registerSub);

	executeInstruction(3, 23, 0);
	printf("Loading value from memory to registerLoad: %d\n", registerLoad);

	executeInstruction(4, 24, 0);
	printf("Storing registerLoad value, %d, into memory[24]\n.", registerLoad);
	printf("Value of memory[24] is: %d\n", memory[24]);

	executeInstruction(5, 2, 2);
	return 0;
}
