/*
 * CS 350, Spring 2013 Weicheng Huang
 * Lab 7: SDC simulator framework
 

Problem solution:
1, assume the other input is b:
a) S	a  b
	 1  1  0 when S = 1 the logic circuit is in a stable status.
	 0  0  1 when S = 0 (assume this change is after stable status) b is also 0
so a turn out to be the 0.	once a=0 , b change to 1 and a also change to 1;
	 when a =1, change back to 0 and b also chagne to 0, which is a unstable status.
b) when S =1,the circuit has a stable value
c) no,becuse this circuit has only one stable status.

2, D | S | Q
	 0 | 0 | if Q =0  before this situation, than Q =0;if Q=1 ,than Q =1
	 0 | 1 | 0
	 1 | 0 | if Q =0 before this situation, than Q =0;if Q=1 ,than Q =1
	 1 | 1 | 1
b) this circuit is always stable
c) yes we can .we can consider D as bit input; S as WE, when we need to change
the value,keep S =1 and change D to what we want first,than change S to 0. the
Q will keep at 0 or 1 no matter D changes.

3,a) x controls a mux that switchs to A+B or A+C
	b) let Cx =~Bx, which will have the 1`s complement of B; we just calculate the
C + A and after this calculation complete, we made output S plus 1(add another 
full adder blow and let one input 0001,the other input S. use a mux to switch if
the result S should calculate in this extra full adder.)(long story,i try to input
a picture here).






*/








#include <stdio.h>
#include <string.h>

// Prototypes
    void helpMsg(void);
		void initCPU(void);
    void readMemory(void);
    void dumpRegisters(int regs[]);
    void dumpMemory(int mem[]);
    int instruction_cycle(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.
//
	int regs[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int mem[100] = { 0 }; // Careful: Leading 0s in constants indicates octal nbr
	int isEnd = 0;
// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("*** STUB *** CS 350 Lab 7, Weicheng Huang\n");
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
	printf("Lab 7 help message is a placeholder\n");
}


// Initialize cpu registers, memory (all to zeros).
//
void initCPU(void) {
	int i;
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
int call_nbr = 0; // For Lab 7, we just print a message and halt after the 10th call
#define min(a, b) (((a) < (b)) ? (a) : (b))
int instruction_cycle(void) {
	int halted = 0;

	// For Lab 7, we just print a message and halt after the 10th call
	//
	++call_nbr;
	char suffix[][4] = {"", "st","nd","rd","th"};
	printf("Calling instruction_cycle for %d%s time\n", call_nbr, suffix[min(call_nbr,4)]);
	if (call_nbr == 10) {
		printf("\nHalting\n");
		halted = 1;
		return 1;
	}
	return 0;
}

