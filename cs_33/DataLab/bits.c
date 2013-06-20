/* 
 * CS:APP Data Lab 
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

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Your login ID */
    "603810706", 
   /* Student name: Replace with the full name */
   "Student name: Eric van Loon",
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
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
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
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
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*
 use of demorgan's laws
 */
  return ~((~x)|(~y));
}


/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {

/*
  First, it shifts a set of 1's left by highbit+1 to give a 
 set of 1's as the left border. Then it negates that set so
 it only includes the correct bits as 1's and 1's to the 
 right of those bits.
  Next, it shifts a set of 1's left by lowbit to have a set 
 including only the correct bits and all those to the left.
  And-ing the 2 sets together results in only the 1's in the 
 correct (desired) bit mask surviving.
 
 the left border is created using <<highbit <<1 instead of
 <<(highbit + 1) to handle the case of highbit = 31 since 
 left shifting by 32 is undefined.
 */
	return ~((~0 << (highbit)) << 1) & ((~0) << lowbit);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
/*
 splits the set in 2 and eliminates pairs of 1's.
 repeats on succesively smaller sets until only 2
 bits are compared.
 */
	x = (x >> 16) ^ x;
	x = (x >> 8) ^ x;
	x = (x >> 4) ^ x;
	x = (x >> 2) ^ x;
	x = (x >> 1) ^ x;
  return x & 1;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
/*
 starting with the relation of A^B being (~A&B)|(A&~B), used 
 demorgan's laws to turn the | into a function of & and ~.
 */
  return ~(~((~x) & y) & ~(x & ~y));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
/*
  turn x into a mask, all 1's if x is false, all 0's if x is true.
 x will be negated to be all 1's if true and all 0's if false, then
 and-ed with y and z.
  the return statement equates to:
 if x is not false, don't eliminate y's bits, if x is not true, 
 don't eliminate z's bits.
 */
  x = ((!x) << 31) >> 31;
  return (~x & y) | (x & z);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
/*
 start with -1, add the opposite of the last digit of x.
 if x%2 is 0, !x%2 is 1, and -1 + 1 = 0. (all 0's)
 if x%2 is 1, !x%2 is 0, and -1 + 0 = -1. (all 1's)
 */
  return (~0) + ((x & 1) ^ 1);
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int evenBits(void) {
/*
 use a small pattern of only even bits and copy it over all the others
 */
  int x = 5;//0101
  x = (x << 4) + x;//01010000 + 0101
  x = (x << 8) + x;
  x = (x <<16) + x;
  return x;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/*
  0xFF is 8 1's in the least significant byte, using & with that will result 
 in a number with some 1's in that byte, and 0's everywhere else. To get the correct
 byte in x to the far right, it is bit shifted by 8*n.
 */
  return 0xFF & (x >> (n << 3));
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
/*
  The variable f is the result of a function that computes the 
 difference in the absolute values of x and y. to do this, x and
 y are forced to have opposite signs, then added to produce a 
 number that is either positive or negative. the sign is xor-ed
 with the sign of x to produce 1 if |x| < |y| and 0 if |x| >= |y|.
  In the return statement, f, now a 0 or a 1, determines which 
 number is closer to 0. if f is 1, y is farther from 0 and the 
 correct answer is the opposite of the sign of y. if f is 0, x is
 closer to 0 and the answer depends on the sign of x.
 */
	unsigned int xSign = x >> 31;
	unsigned int ySign = y >> 31;
	
	//1...1 if x and y are the same sign
	unsigned int changeSign = xSign ^ ~ySign;
	unsigned int f;
	y = ((~y + 1) & changeSign) | (y & ~changeSign);
	//f is the difference in the absolute values, |x| - |y|
	f = (((y + x) ^ xSign) >> 31) & 1;
	
	return ((f & !ySign) | ((!f) & xSign));
}
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
/*
 if x or -x has a 1 in the sign place, it is not 0.
 */
  return (((x | (~x + 1)) >> 31) & 1);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
int isPower2(int x) {
/*
  if x and x-1 have any bits in common (x-1 will eliminate the 
 rightmost 1 in x and put 1's after that, keeping everything 
 else the same), then x is not a power of 2.
  boundary cases are 0 and all negative numbers. To solve x = 0,
 since the above logic will result in a 1, xor-ing that with !x
 will result in a 0 if x = 0 or the result if x is not 0. And-ing
 the combined result of the above with the not of the sign of x,
 0 if x is negative and 1 if x is positive, will eliminate the 
 need to worry about negative numbers (specifically unsigned 1<<32).
 */
  return (!(x & (x + ~0U))  ^  !(x)) & !(x >> 31);
}
/*
 * isZero - returns 1 if x == 0, and 0 otherwise 
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
/*
 !x results in 0 if x is 0, and 1 if x is not
 xor-ing that with 1 will switch the bit
 */
  return !x;
}
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
 if x or -x has a 1 in the sign place, it is not 0. (isNonZero)
 the result of that ^1 will be 1 if x is 0, and 0 if x is not 0.
 */
  return (((x | (~x + 1)) >> 31) & 1) ^ 1;
}
/*
 * multFiveEights - multiplies by 5/8 rounding toward 0.
 *   Examples: multFiveEights(77) = 48
 *             multFiveEights(-22) = -13
 *   You can assume |x| < (1 << 29)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEights(int x) {
/*
  factor out powers of 2 from 5 (ie: 5 = 4+1)
 then change x to: x = 4*x + 1*x
  then divide x by 8 by shifting to the right by 3, 
 but if x is < 0, add 7 before dividing to round 
 up towards 0.
 */
	x = (x << 2) + x;// x * 5
	return (x + ((x >> 31) & 7)) >> 3;// x / 8
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/*
  By the definition, the increment of the complement 
 of the number is the negative of the number.
 */
  return ~x + 1;
}
