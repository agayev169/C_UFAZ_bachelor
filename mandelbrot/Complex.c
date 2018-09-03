/*====================================================*\
  Vendredi 8 novembre 2013
  Arash HABIBI
  Complex.c
\*====================================================*/

#include "Complex.h"

//-------------------------------------------------------

Complex CX_new(scalar real, scalar imgn)
{
	Complex z;
	z._real = real; z._imgn=imgn;
	return z;
}

//-------------------------------------------------------

void CX_check(Complex z, char *message)
{
	fprintf(stderr,"%s : %f + i %f\n",message,z._real,z._imgn);
}

//-------------------------------------------------------

Complex CX_add(Complex z1, Complex z2)
{
	Complex sum;
	sum._real = z1._real + z2._real;
	sum._imgn = z1._imgn + z2._imgn;
	return sum;
}

//-------------------------------------------------------

Complex CX_square(Complex z)
{
	Complex res;
	res._real = z._real*z._real - z._imgn*z._imgn;
	res._imgn = 2*z._real*z._imgn;
	return res;
}

//-------------------------------------------------------

scalar CX_squareModule(Complex z)
{
	return(z._real*z._real+z._imgn*z._imgn);
}
