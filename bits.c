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
   /* Your user ID*/
    "nguy", 
   /* Student name: Replace with the full name */
   "Jonathan Nguy",
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
       /* de morgan's law*/       
       return ~(~x|~y);
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
 Shift set of 1's left by highbit + 1
 Negate it to include correct bits as 1's
 the right bits become 1's
 next, shift set of 1's left by lowbit
	the set will have correct bits and to the left
 and'ing the two will get 1's in needed spots
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
	 split the set into 2 and eliminate double 1's
	 keep going until only 2 bits are compared
	 */
    x = (x >> 16) ^ x;
    x = (x >> 8) ^ x;
    x = (x >> 4) ^ x;
    x = (x >> 2) ^ x;
    x = (x >> 1) ^ x;
    return x&1;
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
	 xor: A^B = (~A&B)|(A&~B)
	 demorgan's law to change | to &
	 
	 */
  return ~(~(~x&y)&~(x&~y));
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
	 turn x into a mask - 1's if x is false, 0's if true
	 x negated to be all 1's if true or 0's if false
	 then and'ed with y and z
	 */
  x = ((!x) << 31) >> 31;  
  return (~x&y)|(x&z);
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
	 add -1 to opposite of the last digit of x
	 if xmod2 = 0, ~xmod2 = 1, and -1 + 1 = 0
	 if xmod2 = 1, ~xmod2 = 0, and -1 + 0 = -1 (1's)
	 
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
	 use a pattern of even bits (5-1010) and copy it over
	 */
  int x=5;
  x = (x<<4)+x;
  x = (x<<8)+x;
  x = (x<<16)+x;
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
	 and'ing with 0xFF to get a byte with 1's in that byte and 0's
	 everywhere else
	 shift by 8*n to get the correct byte in x
	 */
  return 0xFF&(x >>(n<<3));
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
	 f computes absolute difference between x and y
	 x and y must have opposite signs 
	 f (which is 0 or a 1) determines which # is closer to 0, 
	 if f = 1, y is farther from 0 and the answer is opposite sign of y
	 if f = 0, x is closer to 0, and the answer depends on the sign of x
	 */
	
  unsigned int xSign = x >> 31;
  unsigned int ySign = y >> 31;
  
  //1...1 if x&y are same signs
  unsigned int changeSign = xSign ^ ~ySign;
  unsigned int f;
  y = ((~y + 1) & changeSign) | (y & ~changeSign);
	
	//f is the absolute difference between x and y
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
	 if x or -x has a 1 in the sign place, it isn't 0
	 */
  return (((x | (~x+1)) >>31) &1);
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
	 boundary cases are 0 and all negative numbers
	 
	 if x and x-1 have any bits in common, then x is not a power of 2
	 
	 to solve x = 0, 
	 the above will result in 1, so xor'ing with !x will result in 0
	 if x =0 or x if x != 0. and'ing the combined result with the not of the 
	 sign of x, 0 would result if x is neg and 1 if x is pos, will eliminate 
	 the need about neg #'s
	 */
  return (!(x & (x + ~0U)) ^!(x))&!(x >> 31);
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
	 if x is 0, it'll return 1,
	 otherwise, it'll return 0
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
	 if x or -x has a 1 in the sign place, it isn't 0
	 that xor'd 1 will be 1 if x is 0, and 0 otherwise
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
  x = (x << 2) + x; //x*5
  return (x + ((x >> 31) & 7)) >> 3; //x/8
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
	 by definition of negate
	 */
  return ~x + 1;
}
