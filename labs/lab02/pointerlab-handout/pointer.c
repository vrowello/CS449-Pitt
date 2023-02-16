/*
 * pointer.c - Source file with your solutions to the Lab.
 *             This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>. The included file, "common.c" contains a function declaration
 * that should prevent a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "allowed" at the top of the method you are writing.
  4. casting.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc. (unless
     otherwise stated).
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions (unless otherwise stated).
  5. Use any operators not "allowed" at the top of the method you are writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
     greater than or equal to the number of bits in the value being shifted.
     e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
     e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
     Undefined means you do not know what result you will get from the operation.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 */

/*
 * Return the size of an integer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, eFDIStc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int intSize() {
	/*
	-Arrays are Pointers
	-By assigning intPtr1 to intArray, the address stored in intArray is copied to intPtr1
	-intPtr2 is defined as intPtr1 + 1, which is actually (long)intPtr1 + sizeOf(int) at the machine level
	-By casting both intPtr1 and intPtr2 as longs, integer arithmetic can be performed on them
	-The difference in these two values is the number of bytes that make up the data type int
	-This difference is then cast back to an int, and returned as an int
	*/
  int intArray[10];
  int* intPtr1;
  int* intPtr2;
  int result;
  
  *intArray = 0;
  intPtr1 = intArray;
  intPtr2 = intPtr1 + 1;
  
  result = (int)((long)intPtr2 - (long)intPtr1);
  return result;
}

/*
 * Return the size of a double in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int doubleSize() {
  /*
	-Arrays are Pointers
	-By assigning doubPtr1 to doubArray, the address stored in doubArray is copied to doubPtr1
	-doubPtr2 is defined as doubPtr1 + 1, which is actually (long)doubPtr1 + sizeOf(double) at the machine level
	-By casting both doubPtr1 and doubPtr2 as longs, integer arithmetic can be performed on them
	-The difference in these two values is the number of bytes that make up the data type double
	-This difference is then cast back to an int, and returned as an int
	*/
 double doubArray[10];
 double * doubPtr1;
 double * doubPtr2;
 int result;
 
  *doubArray = 0;
  doubPtr1 = doubArray;
  doubPtr2 = doubPtr1 + 1;
  
  result = (int)((long)doubPtr2 - (long)doubPtr1);
  return result;
}

/*
 * Return the size of a pointer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int pointerSize() {
  
  /*
	-Arrays are Pointers
	-By assigning ptrPtr1 to ptrArray, the address stored in ptrArray is copied to ptrPtr1
	-ptrPtr2 is defined as ptrPtr1 + 1, which is actually (long)ptrPtr1 + sizeOf(pointer) at the machine level
	-By casting both ptrPtr1 and ptrPtr2 as longs, integer arithmetic can be performed on them
	-The difference in these two values is the number of bytes that make up the data type double
	-This difference is then cast back to an int, and returned as an int
	*/
  int * ptrArray[10];
  int ** ptrPtr1;
  int ** ptrPtr2;
  int result;
 
  *ptrArray = 0;
  ptrPtr1 = ptrArray;
  ptrPtr2 = ptrPtr1 + 1;
  
  result = (int)((long)ptrPtr2 - (long)ptrPtr1);
  return result;
}

/*
 * Given pointers to two distinct variables write a function to swap the values
 * of said variables.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
void swapInts(int * ptr1, int * ptr2) {
  /*
  -this could should be fairly self explanatory
  -I simply copied the values stored in each pointer to a local variable, then copied the value stored in the variables into the value that 'opposite' pointer's address refers to
  */
  int arg1 = *ptr1;
  int arg2 = *ptr2;
  
  *ptr2 = arg1;
  *ptr1 = arg2;
}

/*
 * Modify intArray[5] to be the value 449 using only intArray and pointer arithmetic.
 * 
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, ~= etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int changeValue() {
	/*
	- 449 = 0x1c1
	- x[i] = *(x + 1)
	*/
  int intArray[10];
  int * intPtr1 = intArray;
  // Remember not to use constants greater than 255.
  // Remember to use * to dereference. You cannot use '[<index>]' syntax.

  *(intPtr1 + 5) = ((0x1c << 4) + 1);
  // replace the line below to use pointer arithmetic
  return *(intPtr1 + 5);
}

/*
 * Return 1 if the addresses stored in ptr1 and ptr2 are within the
 * *same* 64-byte aligned  block of memory. Check the spec for examples if you are
 * confused about what this means. Return zero otherwise.
 * Operators / and % and loops are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int withinSameBlock(int * ptr1, int * ptr2) {
  int case1 = ((((((long)ptr1 - (long)ptr2) - 64) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
  
  int case1b = ((((((long)ptr1 - (long)ptr2)) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
 
  
  int case2 = ((((((long)ptr2 - (long)ptr1) - 64) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
  int case2b = ((((((long)ptr2 - (long)ptr1)) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
  
  /*
  printf("case 1: %d \n", case1);
  printf("case 1b: %d \n", case1b);
  printf("case 2: %d \n", case2);
  printf("case 2b: %d \n", case2b);
  */
  case1 = (case1 ^ case1b);
  case2 = (case2 ^ case2b);
  /*
  printf("case 1: %d \n", case1);
  printf("case 2: %d \n", case2);
  */
  return(!((!case1 + !case2) == 2));
 }

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 * Pointing anywhere in the array is fair game, ptr does not have to
 * point to the beginning of an element. Check the spec for examples if you are 
 * confused about what this method is determining.
 * size is the size of intArray in number of ints. Can assume size != 0.
 * Operators / and % and loops are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int withinArray(int * intArray, int size, int * ptr) {
  /*
  -The goal is to return a boolean value of 0 or 1
  - the value to return is intArray <= ptr  < intArray+size
  -TODO: finish documenting this function
  */
  
  int case1 = ((((((long)ptr - (long)intArray) - (size * 4)) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
  int case2 = (((((long)ptr - (long)intArray) >> 1) ^ (((long)1) << 63)) >> 62) == 1;
  return(case1 ^ case2);
}

/*
 * In C characters are are terminated by the null character ('\0')
 * given a pointer to the start of the string return the length of this string.
 * (The null character is not counted as part of the string length.)
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *   Control constructs: for, while
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /, %
 *   Unary integer operators: ~, -
 */
int stringLength(char * s) {
  /*
  -Iterates through s (copied to c to protect s) until a null character is found, incrementing i
  */
  int i = 0;
  char* c = s;
  while(*c != '\0') {
  	i++;
  	c++;
  }
  return i;
}

/*
 * Returns the length of the initial portion of str1 which consists only of characters that are part of str2.
 * The search does not include the terminating null-characters of either strings, but ends there.
 * 
 * Example, stringSpan("abcdefgh", "abXXcdeZZh"); // returns 5
 *  
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *   Control constructs: for, while
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /, %
 *   Unary integer operators: ~, -
 */
int stringSpan(char * str1, char * str2) {
  /*
  -Iterates through both strings
  -If through an iteration of the second string, no matches are found, the loop breaks
  -If a match is found, str2 is reset, i increments by 1, and the loop continues for the next character in str1
  -I is returned at the end
  */
  int i = 0;
  int j = 1;
  char* str1Copy = str1;
  char* str2Copy = str2;
  
  while(j) {
  	while(*str1 != '\0') {
  		j = 0;
  		while(*str2 != '\0') {
  			while(*str1 == *str2) {
  				goto reset;
  			}
  			str2++;	
  		}
  		break;
  		reset: j = 1;
  		str2 = str2Copy;
  		i++;
  		str1++;
  	}
  	
  }
  
  return i;
  
}

/*
 * Change the value pointed to by ptr byte-by-byte so that when returned as an integer
 * the value is 449449.
 *
 * Hint: Remember that an int is 4 bytes.
 *
 * Hint: Remember how little endian works for data storage, how is it different between an multiple bytes(int) and a single byte?
 *
 * Hint: It will be easiest to start convert 449449 into binary form and starting seeing how the endian works from there.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *   Unary integer operators: !
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int endianExperiment(int * ptr) {
  /*
  - 449449 = 0006DBA9
  */
  char *bytePtr;
  
  bytePtr = (char*)(long)ptr;
  
  *bytePtr = 0xA9;
  bytePtr++;
  
  *bytePtr = 0xDB;
  bytePtr++;
  
  *bytePtr = 0x06;
  bytePtr++;
  
  bytePtr = 0;
  
  return *ptr;
}

/*
 * Selection sort is a sorting algorithim that works by partitioning the array into
 * a sorted section and unsorted section. Then it repeatedly selects the minimum element
 * from the unsorted section and moves it to the end of the sorted section.
 *
 * So the pseudo-code might look something like this:
 * arr - an array
 * n - the length of arr
 *
 * for i = 0 to n - 1
 *   minIndex = i
 *   for  j = i + 1 to n
 *       if arr[minIndex] > arr[j]
 *           minIndex = j
 *       end if
 *   end for
 *   Swap(arr[i], arr[minIndex])
 * end for
 *
 * Implement selection sort below, it might be helpful to use the swapInts function you
 * defined earlier.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *   Control constructs: for, while, if
 *   Function calls: swapInt()
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /
 *   Unary integer operators: ~, -
 */
void selectionSort(int arr[], int arrLength) {
  /*
  - just the implementation of the above pseudocode
  */
  int i, j, min_index;
  i = 0;
  j = 1;
  min_index = 0;
  
  while(i < arrLength - 1) {
  	while(j < arrLength) {
  		if(*(arr + min_index) > *(arr + j)) {
  			min_index = j;
  		}
  		j++;
  	}
  	swapInts((arr + i), (arr + min_index));
  	i++;
  	min_index = i;
  	j = i + 1;
  	
  }
  
}
