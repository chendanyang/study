

/* CS 350, Fall 2012
 * Lab 2 -- Converting an integer to a given base
 *
 * Illinois Institute of Technology, (c) 2013, James Sasaki
 */

/*1:  9 bits , and 112 students can be admitted to the class.
* 2:  -1.101*2^-65 , the decimal value is 
* 3:  1.01101011*2^-6
* 4:  a)0 01111001 01101011000000000000000  b)3CB5 8000
* 5:  Because IEEE floating-point type has only 23 bits to represent * the fraction and as you see, the right " 011" is out of range. so * it can't be represent. b) 11.00000 00000 00000 00000 1 c) 11.00000 * 00000 00000 00000 0
* 6:  a)10.111 There was an error
*     b)1.1111 There was no error
*     c)11.111 There was no error
      d)11.110 There was an error
      d)Yes.
*/
/* This program repeatedly converts a value to a given base.
 * The value is converted to an equivalent array of digits
 * (each >= 0 and < base), and then we print the array.
 * We convert value & base pairs until the value is < 1 or base < 2.
 */
#include <stdio.h>
#include <strings.h>

#define ARRAYLEN 20

/* prototypes */
void break_up(int value, int base, int digits[], int len);
void print_digits(int digits[], int n);
int main() {
	printf("CS 350 Lab 2 for %s\n\n", "Weicheng Huang Section -01");  // <-- Fill in

	int value, base;
	int digits[ARRAYLEN+1];
	/* Read an integer value to convert and the base to convert it to
	 */
	printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
	scanf("%d %d", &value, &base);
	/* Quit if the value is < 1 or the base is < 2.  Otherwise,
	 * call break_up to fill the digits array with values and
	 * then call print_digits to print out the array.  Then
	 * prompt, read another input, and repeat.
	*/

	while (value >= 1 && base >= 2) {
		break_up(value, base ,digits,ARRAYLEN);
		print_digits(digits,ARRAYLEN);
		printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
		scanf("%d %d", &value, &base);
	} 
}






/* break_up takes a value, a base, an array of digits, and
 * the length of the array and converts the value into a
 * sequence that represents the value in the given base.
 * The sequence is stored in the digits array.
 * Formally, on return we should have
 *
 * passed value
 *   = digits[0] * base^(len-1)
 *     + ...
 *     + digits[i] * base^(len-i-1)
 *     + ...
 *     + digits[len-1] * base^0
 *
 * If the value is too large to be represented (we have a
 * value that would need a digits[-1] * base^len position),
 * then we complain and print out the unrepresentable part
 * of the value (namely, passed value / base^len).
 */
void break_up(int value, int base, int digits[], int len){
  int i = len-1;
  for( i ; i >= 0; i--){

       digits[i] =value%base;
       value =value/base;
     }
  digits[20] = value;
  	

}

/* print_digits takes an array of integers and the length of
 * the array and prints out the integers on one line, separated
 * by a space.
 */
void print_digits(int digits[], int n){
  int i = 0;
  for(i = 0;i<ARRAYLEN-1;i++){
    printf("%d ",digits[i]);
  }
  printf("%d \n",digits[n-1]);
  if(digits[20]>0){
    printf("the unrepresentable part = %d \n",digits[20]);
  }
}


