//Project 1 Jonathan Wallace, Christopher Bernal, third person anonymous.
//This project is for the class Operating systems and is composed of 5 modules.
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// use the github as a place to copy and paste code that you need or code that you have written thanks! :D

//Define CPU registers
int PC; //Program Counter
int ACC; //Accumulator
int IR; //Instruction Register
int statusRegister; //Status flags

//Memory (instructions and data)
int memory[] = {333, 122, 120, 215, 205};
int dataMemory[100]; //Data memory

// () -> ()
// intializes the dataMemory in the dataMemory array
// EFFECT: dataMemory array is mutated to be the value of the index number.
void initialize_dataMemory(){
// just to make each dataMemory hold a value
for(int i = 0; i < sizeof(dataMemory); i++){
dataMemory[i] = i;
}
}


//fetch instruction
int fetchInstruction() {
 return memory[PC];
}

// int -> int
// gets the address of the given instruction by removing the first digit in the integer.
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
// gets the first digit of the instruction
int get_opcode(int instruction){
    int first = instruction;
    while(first >= 10)
    {
        first = first / 10;
    }
    return first;
}

//Decode and execute instruction
//signature:int -> none
//purpose: takes an instruction and finds the opcode at which the instruction belongs to.
void executeInstruction(int instruction) {

int opcode = get_opcode(instruction);
int address = get_address(instruction);

    switch (opcode) {
        case 1: // ADD operation
            ACC = ACC + dataMemory[address];
            break;
        case 2: // SUB operation
            ACC = ACC - dataMemory[address];
            break;
        case 3: // LOAD operation
            ACC = dataMemory[address];
            break;
        case 4: // STORE operation
            dataMemory[address] = ACC;
            break;
}

}

//Main loop for CPU operation – eg., fetch-decode-execute loop
int main() {
// initalizing the datamemory.
initialize_dataMemory();
PC = 0;
while (PC < sizeof(memory) / sizeof(memory[0])) {
//Fetch the instrction
IR = fetchInstruction();
//increment PC; move to the next instruction
PC++;
//decode and execute
executeInstruction(IR);

printf("The value of ACC: %d \n",ACC );
printf("The value of IR: %d \n",IR );
printf("The value of PC: %d \n",PC );
printf("\n");
}
 return 0;
}

