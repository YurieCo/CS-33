
//2.66

int left_most_one(unsigned x)
{
	x = x|(x>>1);
	x = x|(x>>2);
	x = x|(x>>4);
	x = x|(x>>8);
	x = x|(x>>16);
	return x;
}


//end 2.66

//2.71

/*
 A) the code does move the correct byte to the correct place,
 but does not format it as a 32 bit integer in 2's complement form.
 */

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
	/*
	 shift left until the correct byte is at the far left,
	 this ensures that the arithmetic copy (forced by casting to
	 an int) will copy the sign of the byte over. shifting right
	 by 24 puts the correct information at the far right and 
	 possibly fills in with 1's for negative numbers.
	 */
	return (int)(word << ((3 - bytenum) << 3)) >> 24;
}

//end 2.71

//2.72

/*
 A) sizeof returns a value that is unsigned, thereby turning the 
 expression on the left of the >= to an unsigned expression.
 this means all values resulting from it will be in the range
 [0, 2^33-1) (using mathematical set notation) and that will
 always be greater than or equal to 0.
 B) conditional test: (maxbytes-(int)sizeof(val) >= 0)
 */

//end 2.72

//2.81

/*
 
 A) no: (tMin, 0)
 B) yes, they are mathematically the same due to associativity 
 and factor of 17 and 15 into powers of 2
 C) yes, 
 ~(x+y) = ~(x+y)+1-1 = -(x+y)-1 = -x-y-y = ~x+1+~y+`-1 = ~x+~y+1
 D) ???
 E) yes, x-(x&3) <= x (x minus the 2 bits at the front is less than x)
 */

//end 2.81

//2.83

/*
 logic:
 if sx and sy are different signs, return sx, if sx is negative, 
 x is the lower value.
 otherwise, x and y have the same sign so return the sign of ux-uy.
 */

unsigned f2u(float f)
{
	return (int) f;
}

int float_le(float x, float y)
{
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);
	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;
	
	return 1 & (((sx ^ sy) & sx) | ((sx ^ sy ^ ~0) & ((ux - uy) >> 31)));
}
//end 2.83

//2.88

/*
 A) yes, floats have 24 bits of signicance (really only 23) so conversion
 from int or double (32 and 53 sig. bits) will always be a loss of precision
 to the same amount.
 B) no, x-y will under/overflow if x and y are large and opposite in sign,
 x = TMin, y = TMax
 C) no, there are only 53 significant bits in doubles and an addition of a 
 very small and a very large number may lose some information.
 dx = 2^-10, dy = 2^60, dz = -2^60
 D) no, overflow may occur on one multiplication but not on another, there 
 are also rounding errors.
 dx = 2*10^30, dy = 2*10^30, dz = 2*10^-30
 E) no, rounding errors? and division by 0 or infinity will make this fail.
 dx = 1, dz = 0
 */

//end 2.88

//2.89

/*
 returns 2^x
 */
float fpwr2(int x)
{
	unsigned exp, frac;
	unsigned u;
	
	if(x < -149)
	{
		/* Too small. Return 0.0; */
		exp = 0;
		frac = 0;
	}
	else if(x < -126)
	{
		/* Denormalized result */
		exp = 0;
		frac = 1 << (149+x);
	}
	else if (x < 127)
	{
		/* Normalized result */
		exp = x;
		frac = 0;
	}
	else
	{
		/* Too big. Return +oo */
		exp = ~0;
		frac = 0;
	}
	
	/* Pack exp and frac into 32 bits */
	u = exp << 32 | frac;
	/* Return as float */
	return u2f(u);
}

//end 2.89

