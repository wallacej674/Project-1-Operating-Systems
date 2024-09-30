#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


// Instruction Codes

#define ADD_operation 1
#define SUB_operation 2
#define LOAD_operation 3
#define STORE_operation 4

// Registers and Memory Arrays
int dataMemory[100];
int memory[] = {333, 122, 120, 215, 205};
int source[] = {1, 2, 3, 4, 5};
int destination[5] = {0};
int DMAsize = sizeof(source) / sizeof(source[0]);
int PC;
int ACC;
int IR;
int savedPC;
int savedACC;
int savedIR;
int statusRegister;
int interruptFlag = 0; // flag to signal the interrupt

typedef struct {
	int* source;
	int* destination;
	int size;
} parametersDMA;

// void -> void
// interrupt handler
void interruptHandler() {
	savedPC = PC;
	savedACC = ACC;
	savedIR = IR;
	printf("Saving CPU status\n");

	printf("Interrupt is being handled.\n");
	sleep(1);
	printf("Restoring CPU status\n");

	interruptFlag = 0;
	printf("Interrupt handling complete!\n");
}

// int -> void
// Check for Interrupt Signals.
void checkForInterrupt(int signal) {
	interruptFlag = 1;
	if (interruptFlag) {
		interruptHandler();
		alarm(2);
	}
}

// int -> void
// Simulate a DMA transfer
void* dmaTransfer(void* args) {
	parametersDMA* params = (parametersDMA*)args;
	int* source = params->source;
	int* destination = params->destination;
	int size = params->size;

	for (int i=0; i < size; i++) {
		printf("Destination index %d now contains %d\n", i, source[i]);
		destination[i] = source[i]; // move data from source to destination
		sleep(2);
		}
}
// int -> void
// Start DMA Transfer
void initiateDMA(int* source, int* destination, int size) {
	// CPU initiates DMA transfer
	printf("Initiating DMA transfer.\n");
	parametersDMA params = {source, destination, size};

	pthread_t dmaThread;
	pthread_create(&dmaThread, NULL, dmaTransfer, &params);
	pthread_detach(dmaThread);
	// CPU can continue with other tasks while transfer happens
}

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

	signal(SIGALRM, checkForInterrupt);
	alarm(1);

	initiateDMA(source, destination, DMAsize);

	while (PC < sizeof(memory) / sizeof(memory[0])) {
		if (!interruptFlag) {
			IR = fetchInstruction();
			PC++;
			executeInstruction(IR);
			sleep(1);
		}
	}
	return 0;
}
