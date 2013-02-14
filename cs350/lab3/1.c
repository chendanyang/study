

/* CS 350, Spring 2013
 * Lab 3 -- Converting Pgm
 *
 * Illinois Institute of Technology, (c) 2013, Weicheng Huang
 */

#include <stdio.h>
#include <strings.h>
#define ARRAYLEN 10


int convert(int digits[]);
void print_digits(int output,int digits[]);
int is_q(char value[]);
int power2(int point);
void translate(char value[],int digits[]);
void reverse(int digits[],int aftrrever[]);
int unsignconver(int digits[]);
int main() {
	printf("\n\n");
	printf("CS 350 Lab 3 for %s\n\n", "Weicheng Huang Section -01");  

	char value[ARRAYLEN];
	int digits[] ={1,1,1,1,1,1,1,1,0,0};
	int output;

	printf("Enter an binary number or 'q' to quit(less than 32 chars):");
	scanf("%s", value);
	//while (is_q(value)==1) {
		//translate(value,digits);
		output = convert(digits);
		print_digits(output,digits);
		printf("Enter an binary number or 'q' to quit(less than 32 chars):");
		scanf("%s", value);
	//} 
	printf("Thank you! see ya!\n\n");
}

int convert(int digits[]){
  int output;
  if(digits[0] ==0){//this is a positive number
    output = unsignconver(digits);
  }else{//this is a negitive number
    int aftrrever[ARRAYLEN];
    reverse(digits,aftrrever);
    output = unsignconver(aftrrever);
    output++;
    output = 0 - output ;
  }
  return output;
}

void reverse(int digits[],int aftrrever[]){

  int i = 0;
  for(i =0;i<ARRAYLEN;i++){
    if(digits[i] == 0){
      aftrrever[i] = 1;
    }else if(digits[i] == 1){
      aftrrever[i] =0;
    }else{
      aftrrever[i] =0;
    }
  }

}

int unsignconver(int digits[]){
  int i;
  int result =0;
  for(i = ARRAYLEN-1;i>=0;i--){
    if(digits[i] ==1){
      result = result + power2(ARRAYLEN-i-1);
    }
  }
  return result;
}
//==========================================================
void translate(char value[],int digits[]){
  int i = 0;
  for(i = 0;i<ARRAYLEN-1;i++){
    if(strcmp(value[i],'0')==0){
      digits[i] = 0;
    }else if (strcmp(value[i],'1')==0){
      digits[i] = 1;
    }else{
      digits[i] = 2;
    }
  }
}
//-------------------------------------
int power2(int point){
  int i;
  long result = 1;
  for(i =0;i<point;i++){
    result = result*2;
  }
  return result;
}

int is_q(char value[]){
  if(strcmp(value[0],'q')==0){
    return 0;
  }else{
    return 1;
  }
}

void print_digits(int output,int digits[]){
  printf("The decimal value : %d \n",output);
  printf("From binary number : ");
  int i = 0;
  for(i = 0;i<ARRAYLEN-1;i++){
    printf("%d",digits[i]);
  }
  printf("%d \n",digits[ARRAYLEN-1]);

}


