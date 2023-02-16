/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
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
  3. Any operators listed as "legal" at the top of the method you are writing.
  4. Shorthand versions of "legal" operators (ex. you can use ++ and += if + is legal)

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
       /* exploit ability of shifts to compute powers of 2 */
       return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
       /* exploit ability of shifts to compute powers of 2 */
       int result = (1 << x);
       result += 4;
       return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
  5. Write comments for your functions! These won't be graded, but it's good
     practice to write comments and may help you debug your code. See the
     above example to see what the comments should look like.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */
#endif

//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/*
	x^y = (x|y) & ~(x&y)
	(x|y) = ~((~x)&(~y))
	x^y = ~((~x)&(~y)) & ~(x&y)
	*/
    return(~((~x)&(~y)) & ~(x&y));
}

//2
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  /*
  max = 0x7FFFFFFF
  0x7FFFFFFF = ~0x80000000;
  0x80000000 = 1000 0000 0000 0000
  			 = 1<<31
  	
  */
  return (~(1<<31));
}
//3
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	/*
	mask = ~(FFFFFFFF << (32-n))
		 	-This creates a word with n zeroes on the left and 32-n ones on the right
		 = ~((~1 + 1) << (32-n))
		 = ~((~1 + 1) << (32 + ~n + 1))
		 = ~((((~1) + 1) << (31 + (~n + 1))) << 1)
		 	-These steps refactored the expression to comply with the operator constraints of this problem
	result = mask & (x>>n)
	       	-By applying the mask, the leading ones are discarded
	*/
    return (~((((~1) + 1) << (31 + (~n + 1))) << 1)) & (x>>n);
}

//4
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/*
	mask = 0xAAAAAAAA
	
	byte = (((x>>24 ^ 0xAA) | (x>>16 ^ 0xAA) | (x>>8 ^ 0xAA) | (x ^ 0xAA)) & 0xAA)
		-For every byte of x, the XOR negates the odd bits
		-By comparing these bytes via OR, we ensure that if any of these bytes contains a 1 in the odd bit, it is accounted for.
		-The result is then compared with 0xAA, discarding the even bits and always leaving 0 if all odd bits in x were 1 and a nonzero value if not
	
	return = !byte
		-since the previous step created a boolean result, we can simply apply a boolean negation to return 1 if all odd bits in x were 1, else 0
	
	*/
    return !(((x>>24 ^ 0xAA) | (x>>16 ^ 0xAA) | (x>>8 ^ 0xAA) | (x ^ 0xAA)) & 0xAA);
}

//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/*
	y = y & (~(!!x) + 1)
		-When x=0, y=0
		-When x!=0, y=y
	z = z & (~(!x) + 1)
		-When x=0, z=z
		-When x!=0, z=0
	return y | z	
	*/
    return (y & (~(!!x) + 1)) | (z & (~(!x) + 1));
}

//6
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/*
	-The only integer without a twos-complement negative is 0 (0000 -> 1111 -> 0000)
	-This means that for EVERY non-zero integer x, either x or -x has a MSB of 1, while the MSB of 0 is ALWAYS 0
	-This means, with an OR comparison of x and -x followed a right shift and a AND comparison to 1, we can reduce any integer to a value of 0 or 1
	-This can then be negated via an XOR comparison to 1
	*/
    return (((x | (~x +1))>>31 & 1)) ^ 1;
}

//7
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	/*
	-if the exponent = 11111111, return 0x80000000u
	
	-if exponent adjusted for bias is 31 or more, which by default includes infinity and NaN, the float is out of the integer type's range
	-if exponent adjusted for bias is less than 0, the fractional bits are truncated, returning 0
	-result is 1<<exponent + mantissa<<(exponent-23) unless exponent is less than 23,then it is ... + mantissa>>(23-exponent)
	*/
	int exp = ((uf >> 23) & 0xFF) - 127;
	int mantissa = ((uf & 0xFF) + (uf & (0xFF << 8)) + (uf & (0x7F << 16)));
	int result = 1;
	int sign = (uf>>31) & 1;
	
    if((exp) > 30) {
    	return 0x80000000u;
    }
    
    if((exp) < 0) {
    	return 0;
    }
    
    
    if(exp > 0) {
    	result = 1 << exp;
    	if(exp < 23) {
    		result = result + (mantissa << ((exp) -23));
    	} else {
    		result = result + (mantissa << ((exp) -23));
    	}
    }
    
    if(sign) {
    	result = result * -1;
    }
    return result;
    
    
}
