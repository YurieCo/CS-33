/* Testing Code */

#include <limits.h>
int test_bitAnd(int x, int y)
{
  return x&y;
}
int test_bitMask(int highbit, int lowbit)
{
  int result = 0;
  int i;
  for (i = lowbit; i <= highbit; i++)
    result |= 1 << i;
  return result;
}
int test_bitParity(int x) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result ^= (x >> i) & 0x1;
  return result;
}
int test_bitXor(int x, int y)
{
  return x^y;
}





int test_conditional(int x, int y, int z)
{
  return x?y:z;
}
int test_copyLSB(int x)
{
  return (x & 0x1) ? -1 : 0;
}
int test_evenBits(void) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i+=2)
    result |= 1<<i;
  return result;
}
int test_getByte(int x, int n)
{
  union {
    int word;
    unsigned char bytes[4];
  } u;
  int test = 1;
  int littleEndian = (int) *(char *) &test;
  u.word = x;
  return littleEndian ? (unsigned) u.bytes[n] : (unsigned) u.bytes[3-n];
}
int test_isLess(int x, int y)
{
  return x < y;
}
int test_isNonZero(int x)
{
  return x!=0;
}
int test_isPower2(int x) {
  int i;
  for (i = 0; i < 31; i++) {
    if (x == 1<<i)
      return 1;
  }
  return 0;
}
int test_isZero(int x) {
  return x == 0;
}
int test_logicalNeg(int x)
{
  return !x;
}
int test_multFiveEights(int x)
{
  return (x*5)/8;
}
int test_negate(int x) {
  return -x;
}
