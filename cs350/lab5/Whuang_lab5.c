//===================include the library=======================
#include <stdio.h>
#define ARRAYLEN 32

//=====================define the sub function============================
void toBinary(int value, int base, int digits[]);
int toDecimal(int digits[]);
void print(int origin,int value,int times);
void rshift_a(int digits[]);
void rshift_l(int digits[]);
void testp(int digits[]);
//=====================define the sub sub function================================
int power2(int point);
void reverse(int digits[]);
int unsignconver(int digits[]);

//=======================here we go!========================================
main ()
{
//title
	printf("\n\n");
	printf("******CS 350 Lab 5 for %s  ******\n\n", "Weicheng Huang Section -01");  
	printf("\n\n");
//initial declare the varibles
	char opt[ARRAYLEN];
	int digits[ARRAYLEN];
	int origin;
        int value;
//begin the loop

	printf("Enter X (0 to stop):");
	scanf("%d", &origin);

	while(origin != 0){
	  printf("Type to shift?(a - arithmetic,l - logical):");
	  scanf("%s", opt);
	  value = origin;
          int times = 1;
	  print(origin,value,0);//the first time to output the shift
	  toBinary(origin,2,digits);
          for(times;times<32;times++){
		if(opt[0] == 'a'){
		  rshift_a(digits);
		  value = toDecimal(digits);
		  print(origin,value,times);
		}else if(opt[0] == 'l'){
		  rshift_l(digits);
		  value = toDecimal(digits);
		  print(origin,value,times);
		}else{
		  printf("You have input a wrong type of shift! Please input 'a' or 'l' again\n");
		}
	  }
	printf("Enter X (0 to stop):");//scan the input for next time use
	scanf("%d", &origin);
        }
//end the loop and thank the user
        printf("Thank you! see Ya!\n");	

}

//========================sub function ========================
void toBinary(int value, int base, int digits[]){
  int i = ARRAYLEN-1;
  if(value>0){
    for( i ; i >= 0; i--){

         digits[i] =value%base;
         value =value/base;
       }
    digits[ARRAYLEN-1] = value;
  }else if(value<0){
    value++;
    value = 0-value;
    for( i ; i >= 0; i--){

         digits[i] =value%base;
         value =value/base;
       }
    digits[ARRAYLEN-1] = value;
    int aftrrever[ARRAYLEN];
    reverse(digits);
   }else{
     i = 0;
     for( i ; i <ARRAYLEN; i++){

         digits[i] =0;
       }
   }
}

int toDecimal(int digits[]){
  int output;
  if(digits[0] ==0){//this is a positive number
    output = unsignconver(digits);
  }else{//this is a negitive number
    int aftrrever[ARRAYLEN];
    int aft[ARRAYLEN];
    int k;
    for(k = 0;k<ARRAYLEN;k++){
	aft[k] = digits[k];
    }
    reverse(aft);
    output = unsignconver(aft);
    output++;
    output = 0 - output ;
  }
  return output;
}

void print(int origin,int value,int times){
printf("%X >> %d = %X                ",origin, times, value);
printf("%d >> %d = %d \n",origin,times,value);
}

void rshift_a(int digits[]){
  int i = ARRAYLEN-1;
  for(i;i>0;i--){
      digits[i] = digits[i-1];
  }

  if(digits[0] == 0){//this is a passtive number
     digits[0] = 0;

  }else{//this is a negative number
    digits[0] = 1;

  }
}

void rshift_l(int digits[]){
    int i = ARRAYLEN-1;
    for(i;i>0;i--){
      digits[i] = digits[i-1];
    }
    digits[0] = 0;
}
void testp(int digits[]){
  int i = 0;
  for (i ; i<ARRAYLEN-1;i++){
    printf("%d",digits[i]);
  }
    printf("%d\n",digits[ARRAYLEN-1]);
}
//========================sub sub function========================
int power2(int point){
  int i;
  long result = 1;
  for(i =0;i<point;i++){
    result = result*2;
  }
  return result;
}

void reverse(int digits[]){

  int i = 0;
  for(i =0;i<ARRAYLEN;i++){
    if(digits[i] == 0){
      digits[i] = 1;
    }else if(digits[i] == 1){
      digits[i] =0;
    }else{
      digits[i] =0;
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

