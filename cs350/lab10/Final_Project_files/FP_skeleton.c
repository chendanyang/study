// CS 350, Final Project, Spring 2013 (skeleton file)
//
// LC3 simulator

#include <stdio.h>
#include <string.h>

// Basic Declarations
//
	typedef short int Word;
	typedef unsigned short int Address;

	#define MEMLEN 65536
	#define NBR_REGS 8


	typedef struct {
		Word memory[MEMLEN];
		Word reg[NBR_REGS];  // Note: "register" is a reserved word
		int condition_code;  // 1=positive, 2=zero, 3=negative
		Word instr_reg;
		Address pgm_counter;
		int running;         // running = 1 iff CPU is executing instructions
	} CPU;


// Prototypes
//
	// CPU manipulation functions
	//
	void init_CPU(CPU *cpu);
	Word get_memory(CPU *cpu, Address addr);
	void set_memory(CPU *cpu, Address addr, Word value);
	void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only);
	Word get_register(CPU *cpu, int regNbr);
	void set_register(CPU *cpu, int regNbr, Word newValue);
	void dump_registers(CPU *cpu);
	char get_condition_code(CPU *cpu);
	void set_condition_code(CPU *cpu, Word value);
  void readfile(CPU *cpu);
	// Instruction cycle functions
	//
	void fetch_instr(CPU *cpu);
	void instruction_cycle(CPU *cpu);
	void helpMsg(void);
	// Functions for executing each instruction.
	// TRAP uses readchar() to read a character (GETC, IN).
	//
  int op(Word opcode);
	void instr_ADD (CPU *cpu);
	void instr_AND (CPU *cpu);
	void instr_BR  (CPU *cpu);
	void instr_err (CPU *cpu);
	void instr_JMP (CPU *cpu);
	void instr_JSR (CPU *cpu);
	void instr_LD  (CPU *cpu);
	void instr_LDI (CPU *cpu);
	void instr_LDR (CPU *cpu);
	void instr_LEA (CPU *cpu);
	void instr_NOT (CPU *cpu);
	void instr_RTI (CPU *cpu);
	void instr_ST  (CPU *cpu);
	void instr_STI (CPU *cpu);
	void instr_STR (CPU *cpu);
	void instr_TRAP(CPU *cpu);
	int  readchar();

	/* *** STUB *** You may need other functions; depends on how you organize your code. */

// -------------------- MAIN PROGRAM --------------------
//
int main() {
	// Declare and initialize the CPU
	//
  printf(" ******************** STUB ********************\n ");
  printf("Lab10 CS350 Author:Weicheng Huang\n");
  CPU cpu;
  init_CPU(&cpu);
  readfile(&cpu);
	printf("\nRegisters:\n");
	dump_registers(&cpu);

	printf("\nMemory:\n");
//	dumpMemory(&cpu,origin,);
  
	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	char command[80];
	fgets(command, sizeof command, stdin);	
	while(cpu.running==1){
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);		// Read past end of current line.
		char op = command[0];		
		switch(op){
			case 'q':
				cpu.running = 0;
				break;		
			case 'h':
				helpMsg();
				break;
			case '?':
				helpMsg();
				break;
			case 'r':
				printf("\nRegisters:\n");
				dump_registers(&cpu);
				break;
			case 'm':
//		dump_memory(&cpu);
				break;
			default:
				instruction_cycle(&cpu);
				break;
		}
	}
/*
		if(command[0] == 'q'){
			c.running = 0;
		}else if(command[0] == 'h'||command[0]=='?'){
			helpMsg();
		}else{
			c.running=instruction_cycle(&c);
		}
*/


	
	

	printf("\nRegisters:\n");
	dump_registers(&cpu);

	printf("\nMemory:\n");
	//dumpMemory(&c);
	/* *** STUB *** */
}

// -------------------- CPU ROUTINES --------------------
//
//
void init_CPU(CPU *cpu) {
	cpu->pgm_counter = 0;
	cpu->instr_reg = 0;
	cpu->condition_code = 0 /*** STUB ***/;  // Z condition code on power-up
	cpu->running = 1;               // CPU is running

	int regNbr = 0;
	while (regNbr < NBR_REGS) {
		set_register(cpu, regNbr++, 0);
	}

	Address addr = 0;
	while(addr<MEMLEN) {
		cpu->memory[addr] = 0;
		addr++;
	}
}

// -------------------- MEMORY ROUTINES --------------------
//

// get_memory(cpu, addr) returns the Word at the cpu's memory address
//
Word get_memory(CPU *cpu, Address addr) {
	return cpu->memory[addr];
}

// set_memory(cpu, addr, value) copies the value to the cpu's memory address
//
void set_memory(CPU *cpu, Address addr, Word value) {
	cpu->memory[addr] = value;
}


// Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu) {
	cpu->instr_reg = cpu->memory[cpu->pgm_counter];
	cpu->pgm_counter = (cpu->pgm_counter + 1) % MEMLEN;
}
  void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only){}
  void dump_registers(CPU *cpu){}
	Word get_register(CPU *cpu, int regNbr){}
	void set_register(CPU *cpu, int regNbr, Word newValue){}

	char get_condition_code(CPU *cpu){}
	void set_condition_code(CPU *cpu, Word value){}

// Execute an instruction cycle
//   Fetch an instruction
//   Decode the instruction opcode
//   Execute the instruction
//
void instruction_cycle(CPU *cpu) {
	// Get current instruction to execute and its location,
	// echo them out.
	//
	Address old_pc = cpu->pgm_counter;
	fetch_instr(cpu);
	printf("x%04hX: x%04hX  ", old_pc, cpu->instr_reg);

	// Execute instruction; set halt = 1 if execution is to stop
	// (TRAP HALT or internal error).
	//
	switch (op(cpu->instr_reg)) {
	case  0: instr_BR(cpu);   break;
	case  1: instr_LD(cpu);   break;
	case  2: instr_ST(cpu);   break;
	case  3: instr_err(cpu);   break;
	case  4: instr_JSR(cpu);   break;
	case  5: instr_AND(cpu);   break;
	case  6: instr_LDR(cpu);   break;
	case  7: instr_STR(cpu);   break;
	case  8: instr_LDR(cpu);   break;
	case  9: instr_NOT(cpu);   break;
	case  10: instr_LDI(cpu);   break;
	case  11: instr_STI(cpu);   break;
	case  12: instr_JMP(cpu);   break;
	case  13: instr_STI(cpu);   break;
	case  14: instr_LEA(cpu);   break;
	case  15: instr_TRAP(cpu);   break;
	default: printf("Bad opcode: %d; quitting\n", op(cpu->instr_reg)); cpu->running = 0; break;
	}
}
	/* *** STUB *** */

/* /\* 	default: *\/ */
/* /\* 		printf("Bad opcode: %d; quitting\n", op(cpu->instr_reg)); *\/ */
/* /\* 		cpu->running = 0; *\/ */
/* /\* 	} *\/ */
/* /\* } *\/ */
	void instr_ADD (CPU *cpu)	{printf("Im working..");}
	void instr_AND (CPU *cpu) {printf("Im working..");}
	void instr_BR  (CPU *cpu)	{printf("Im working..");}
	void instr_err (CPU *cpu)	{printf("Im working..");}
	void instr_JMP (CPU *cpu)	{printf("Im working..");}
	void instr_JSR (CPU *cpu)	{printf("Im working..");}
	void instr_LD  (CPU *cpu)	{printf("Im working..");}
	void instr_LDI (CPU *cpu)	{printf("Im working..");}
	void instr_LDR (CPU *cpu)	{printf("Im working..");}
	void instr_LEA (CPU *cpu)	{printf("Im working..");}
	void instr_NOT (CPU *cpu)	{printf("Im working..");}
	void instr_RTI (CPU *cpu)	{printf("Im working..");}
	void instr_ST  (CPU *cpu)	{printf("Im working..");}
	void instr_STI (CPU *cpu)	{printf("Im working..");}
	void instr_STR (CPU *cpu)	{printf("Im working..");}
	void instr_TRAP(CPU *cpu)	{printf("Im working..");}
/* /\* // Execute branch instruction: Bitwise AND instruction's mask and *\/ */
/* /\* // cpu's condition code, branch iff result is nonzero. *\/ */
/* /\* // *\/ */
/* /\* // Echo kind of branch, current cc, whether or not branch happened, *\/ */
/* /\* // and if so, the target of the branch. *\/ */
/* /\* // *\/ */
/* /\* void instr_BR(CPU *cpu) { *\/ */
/* /\* 	printf("BR instruction; *** STUB ***\n"); *\/ */


/* *** STUB *** */

	int op(Word opcode){
		return opcode>>12;
	}
// Read and return a character from standard input.  User must
// enter return after the char.  Just pressing return causes \n
// to be returned.  Any extra characters after the first are ignored.
//
int read_char() {
	char buffer[3] = "";
	fgets(buffer, sizeof buffer, stdin);
	return buffer[0];
}

void readfile(CPU  *cpu){
		char name[100];
		printf("please tell me the name of the file:");
    fgets(name, sizeof name, stdin);
    FILE *f;
    unsigned int num[80];

    f=fopen(name,"r");
    while (f==NULL){
    	printf("\nfile doesnt exist?!\n");
		  printf("please tell me the name of the file:");
    	fgets(name, sizeof name, stdin);
   	  f=fopen(name,"r");
    }
		unsigned int temp =0;
    fscanf(f,"%x",&temp);
		cpu->pgm_counter = temp;
		int i = temp;
		cpu->memory[i] = temp;

    while (fscanf(f,"%x",&temp) != EOF){
			cpu->memory[i] = temp;
    	i++;
    }
    fclose(f);
}
	void helpMsg(void){}
/* *** STUB *** */
