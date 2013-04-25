/*
 * CS 350, Spring 2013 Weicheng Huang
 * Lab 9: SDC simulator 

Prblem
1)
	int b[]={3,4,6,8};
	int *q,*p,*r;
	p=&b[0];
	q=&b[1];
	r=&b[2];
2)
	a) no ev to true
	b) no ev to true
	c) compile error
	d) no ev to ture
	e) no ev to ture

3)
	p1)
	b | 0 | 1 | 2     | 3 |
	   12  13  14 <-z   15
	u = 20  <- y 
	x = 20(different address with &u)  
	v = 30

	p2)
	b | 0 | 1 | 2     | 3 |
	   12  13  14 <-z   20
	u = 20  
	x = 21(different address with &u)  
	v = 30  <- y 
   
4)
	a) no no ture
	b) yes lack of type transformation when compairing not related pointer
	c) no no ture
	d) no no ture
	e) yes unidentifier a
*/

#include <stdio.h>
#include <math.h>
typedef int word;
typedef int address;
#define MEM_LEN 100
#define REG_LEN 10
typedef struct{
  word mem[MEM_LEN];
  word regs[REG_LEN];
  address pc;
  word ir;
  int running;
  int opcode;
  int radd;
  int mmadd;
} CPU;
// Prototypes
void helpMsg(void);
void initCPU(CPU *cpu);
void readMemory(CPU *cpu);
void dumpRegisters(CPU *cpu);
void dumpMemory(CPU *cpu);
int instruction_cycle(CPU *cpu);
void ld(CPU *cpu);//1
void st(CPU *cpu);//2
void add(CPU *cpu);//3
void neg(CPU *cpu);//4
void ldm(CPU *cpu);//5
void addm(CPU *cpu);//6
void br(CPU *cpu);//7
void brp(CPU *cpu);//8
void io(CPU *cpu);//9
void handleInstruction(CPU *cpu);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up. 

//
//	int regs[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//	int mem[100] = { 0 }; // Careful: Leading 0s in constants indicates octal nbr
//	int isEnd = 0;
//	int pc;
//	int ir;
//	int opcode;//operation code
//	int radd;//register address
//	int mmadd;//memory address
// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
  printf(" ******************** STUB ********************\n ");
	printf("Lab9 CS350 Author:Weicheng Huang\n");
	CPU c;
	initCPU(&c);
	readMemory(&c);

	printf("\nBeginning execution:\n");
	printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
	char prompt[] = "> ";
	char command[80];
	fgets(command, sizeof command, stdin);	
	while(c.running==1){
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);		// Read past end of current line.

		if(command[0] == 'q'){
			c.running = 0;
		}else if(command[0] == 'h'||command[0]=='?'){
			helpMsg();
		}else{
			c.running=instruction_cycle(&c);
		}
	
	}

	
	

	printf("\nRegisters:\n");
	dumpRegisters(&c);

	printf("\nMemory:\n");
	dumpMemory(&c);
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
	printf("Lab 9 help message is a placeholder\n");
}


// Initialize cpu registers, memory (all to zeros).
//
void initCPU(CPU *cpu) {
	int i;
	
	(*cpu).pc=0;
	(*cpu).ir=0;
  (*cpu).running=1;
  (*cpu).opcode=0;
  (*cpu).radd=0;
  (*cpu).mmadd=0;
	for (i = 0; i < 10; i++) (*cpu).regs[i] = 0;
	for (i = 0; i < 100; i++) (*cpu).mem[i] = 0;
}

// Read and dump initial values for memory
//
void readMemory(CPU *cpu) {
	
	int loc = 0;
	int temp;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");
	//loop for input the value
	printf("Loc %02d: ",loc);
	scanf("%d", &temp);
	while((temp<=9999)&&(temp>=-9999)){		
			(*cpu).mem[loc] = temp;		
			loc++;	
			printf("Loc %02d: ",loc);
			scanf("%d", &temp);
	}
	printf("\nInitial value of memory:\n");
	dumpMemory(cpu);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(CPU *cpu) {
	int j;
	
	for(j = 0;j<5;j++){
			printf("  R%d: % 05d",j,(*cpu).regs[j]);
	}
	printf("\n");

	for(j=5;j<10;j++){
			printf("  R%d: % 05d",j,(*cpu).regs[j]);
	}
	printf("\n");

}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(CPU *cpu) {
	int i,j;
	
	for(i = 0;i<=9;i++){
		printf("  %02d: ",i*10);
		for(j = 0;j<5;j++){
				printf("% 05d ",(*cpu).mem[i*10+j]);
		}
		printf(" ");
		for(j=5;j<10;j++){
				printf("  % 05d ",(*cpu).mem[i*10+j]);	
		}
		printf("\n");
	}
}


// Execute one instruction cycle.
//
#define min(a, b) (((a) < (b)) ? (a) : (b))
int instruction_cycle(CPU *cpu) {
	int halted = 1;
	
	(*cpu).ir = (*cpu).mem[(*cpu).pc];
	handleInstruction(cpu);
	switch ((*cpu).opcode){
		case 0:
		  halted = 0;
		  printf("Halt!");
		  break;
		case 1:
		  ld(cpu);
		  break;
		case 2:
		  st(cpu);	
		  break;
		case 3:
		  add(cpu);
		  break;
		case 4:
		  neg(cpu);
		  break;
		case 5:
		  ldm(cpu);
		  break;
		case 6:
		  addm(cpu);
		  break;
		case 7:
		  br(cpu);
		  break;
		case 8:
		  brp(cpu);
		  break;
		case 9:
		  io(cpu);
		  break;
		default:
		  printf("Error:Invalid opcode at address %d,Invalid number: %d",(*cpu).pc,(*cpu).mem[(*cpu).pc]);
		  break;
	}
	(*cpu).pc++;
	return halted;
	// For Lab 7, we just print a message and halt after the 10th call
	//
	//char suffix[][4] = {"", "st","nd","rd","th"};
	//printf("Calling instruction_cycle for %d%s time\n", call_nbr, suffix[min(call_nbr,4)]);

}
//  handle
void handleInstruction(CPU *cpu){
  
  if((*cpu).ir<0){
    (*cpu).ir = 0-(*cpu).ir;
  }
  (*cpu).opcode = (int)((*cpu).ir/1000);
  //printf("opcode is %d \n",opcode);
  (*cpu).radd = (int)(((*cpu).ir-(*cpu).opcode*1000)/100);
  //printf("register address is %d \n",radd);
  (*cpu).mmadd = (*cpu).ir-(*cpu).opcode*1000-(*cpu).radd*100;
  //printf("memary address is %d \n",mmadd);
}		
//opcode operation
		void ld(CPU *cpu){//1
		  	
		  (*cpu).regs[(*cpu).radd] = (*cpu).mem[(*cpu).mmadd];
			printf("Load register %d from memory location %02d\n",(*cpu).radd,(*cpu).mmadd);
		}

		void st(CPU *cpu){//2
		  
		  (*cpu).mem[(*cpu).mmadd] = (*cpu).regs[(*cpu).radd];
		  printf("Store register %d into memory location %02d\n",(*cpu).radd,(*cpu).mmadd);
		}

		void add(CPU *cpu){//3
		  
		  (*cpu).regs[(*cpu).radd] +=(*cpu).mem[(*cpu).mmadd];
		  printf("Add contents of memory location %02d to register %d\n",(*cpu).mmadd,(*cpu).radd);
		}

		void neg(CPU *cpu){//4
		  
		  (*cpu).regs[(*cpu).radd] = 0-(*cpu).regs[(*cpu).radd];
		  printf("Set register %d to its arithmetic negative(ignore %02d)\n",(*cpu).radd,(*cpu).mmadd);
		}

		void ldm(CPU *cpu){//
		  
		  (*cpu).regs[(*cpu).radd] = (*cpu).mmadd;
		  printf("Load register %d with %02d(not the contents of MM)\n",(*cpu).radd,(*cpu).mmadd);
		}

		void addm(CPU *cpu){//6
		  
			(*cpu).regs[(*cpu).radd] +=(*cpu).mmadd;
			printf("Add %02d to register %d\n",(*cpu).mmadd,(*cpu).radd);
		}

		void br(CPU *cpu){//7
		  
		  (*cpu).pc = (*cpu).mmadd;
		  printf("Go to location %02d(ignore R)\n",(*cpu).mmadd);
		}

		void brp(CPU *cpu){//8
		  
		  if((*cpu).regs[(*cpu).radd]>0){
				(*cpu).pc = (*cpu).mmadd;
			}
			printf("Go to location %02d if register %d contains a value strictly greater than zero\n",(*cpu).mmadd,(*cpu).radd);
		}

		void io(CPU *cpu){//9
		  
		  char temp;
		  switch((*cpu).radd){
		  case 0:
		    printf("please input a character:");
		    scanf("%s\n",&temp);
		    (*cpu).regs[0] = temp;
		    break;
		  case 1:
		    printf("%d\n",(*cpu).regs[0]);
		    break;
		  case 2:
		    while((*cpu).mem[(*cpu).mmadd]!=0){
		      printf("%d",(*cpu).mem[(*cpu).mmadd]);
		      (*cpu).mmadd++;
		    }
		    printf("\n");
		    break;
		  case 3:
		    printf("%d\n",(*cpu).regs[(*cpu).radd]);
		    break;
		  case 4:
		    dumpMemory(cpu);
		    break;
		  default:
		    printf("Error: You have input a ignore instruction %05d",(*cpu).mem[(*cpu).mmadd]);
		  }
		}
