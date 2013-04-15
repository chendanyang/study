/*
 * CS 350, Spring 2013 Weicheng Huang
 * Lab 8: SDC simulator 







*/








#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Prototypes
    void helpMsg(void);
		void initCPU(void);
    void readMemory(void);
    void dumpRegisters(int regs[]);
    void dumpMemory(int mem[]);
    int instruction_cycle(void);
		void ld(void);//1
		void st(void);//2
		void add(void);//3
		void neg(void);//4
		void ldm(void);//5
		void addm(void);//6
		void br(void);//7
		void brp(void);//8
		void io(void);//9
		void handleInstruction(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.
//
	int regs[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int mem[100] = { 0 }; // Careful: Leading 0s in constants indicates octal nbr
	int isEnd = 0;
	int pc;
	int ir;
	int opcode;//operation code
	int radd;//register address
	int mmadd;//memory address
// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("*** STUB *** CS 350 Lab 8, Weicheng Huang\n");
	initCPU();
	readMemory();

	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	char command[80];
	fgets(command, sizeof command, stdin);	
	while(isEnd==0){
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);		// Read past end of current line.

		if(command[0] == 'q'){
			isEnd = 1;
		}else if(command[0] == 'h'||command[0]=='?'){
			helpMsg();
		}else{
			isEnd=instruction_cycle();
		}
	
	}

	
	

	printf("\nRegisters:\n");
	dumpRegisters(regs);

	printf("\nMemory:\n");
	dumpMemory(mem);
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
	printf("Lab 8 help message is a placeholder\n");
}


// Initialize cpu registers, memory (all to zeros).
//
void initCPU(void) {
	int i;
	pc=0;
	ir=0;
	for (i = 0; i < 10; i++) regs[i] = 0;
	for (i = 0; i < 100; i++) mem[i] = 0;

}

// Read and dump initial values for memory
//
void readMemory(void) {
	int loc = 0;
	int temp;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");
	//loop for input the value
	printf("Loc %02d: ",loc);
	scanf("%d", &temp);
	while((temp<=9999)&&(temp>=-9999)){		
			mem[loc] = temp;		
			loc++;	
			printf("Loc %02d: ",loc);
			scanf("%d", &temp);
	}
	printf("\nInitial value of memory:\n");
	dumpMemory(mem);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(int regs[]) {
	int j;

	for(j = 0;j<5;j++){
			printf("  R%d: % 05d",j,regs[j]);
	}
	printf("\n");

	for(j=5;j<10;j++){
			printf("  R%d: % 05d",j,regs[j]);
	}
	printf("\n");

}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(int mem[]) {
	int i,j;
		
	for(i = 0;i<=9;i++){
		printf("  %02d: ",i*10);
		for(j = 0;j<5;j++){
				printf("% 05d ",mem[i*10+j]);
		}
		printf(" ");
		for(j=5;j<10;j++){
				printf("  % 05d ",mem[i*10+j]);	
		}
		printf("\n");
	}
}


// Execute one instruction cycle.
//
#define min(a, b) (((a) < (b)) ? (a) : (b))
int instruction_cycle(void) {
	int halted = 0;
  ir = mem[pc];
	handleInstruction();
	switch (opcode){
		case 0:
			halted = 1;
			break;
		case 1:
			ld();
			break;
		case 2:
			st();	
			break;
		case 3:
			add();
			break;
		case 4:
			neg();
			break;
		case 5:
			ldm();
			break;
		case 6:
			addm();
			break;
		case 7:
			br();
			break;
		case 8:
			brp();
			break;
		case 9:
			io();
			break;
		default:
			Printf("Error:Invalid opcode at address %d,Invalid number: %d",pc,mem[pc]);
			break;
	}
	pc++;
	return halted;
	// For Lab 7, we just print a message and halt after the 10th call
	//
	//char suffix[][4] = {"", "st","nd","rd","th"};
	//printf("Calling instruction_cycle for %d%s time\n", call_nbr, suffix[min(call_nbr,4)]);

}
//  handle
		void handleInstruction(){
		if(ir<0){
			ir = 0-ir;
		}
		char[] buffer;
		itoa(ir,buffer,10);
		opcode = buffer[0] - '0';
		radd = buffer[1] -'0';
		int temp = buffer[2]-'0';
		int memadd = buffer[3]-'0';
		memadd +=temp*10;
		
//opcode operation
		void ld(void){//1
			printf("ld at %02d: %04d",pc,mem[pc]);
		}
		void st(void){//2
			printf("st at %02d: %04d",pc,mem[pc]);
		}
		void add(void){//3
			printf("st at %02d: %04d",pc,mem[pc]);
		}
		void neg(void){//4
			printf("st at %02d: %04d",pc,mem[pc]);
		void ldm(void){//5
			printf("st at %02d: %04d",pc,mem[pc]);
		void addm(void){//6
			printf("st at %02d: %04d",pc,mem[pc]);
		void br(void){//7
			printf("st at %02d: %04d",pc,mem[pc]);
		void brp(void){//8
			printf("st at %02d: %04d",pc,mem[pc]);
		void io(void){//9
			printf("st at %02d: %04d",pc,mem[pc]);


