/*====================================================*\
  Vendredi 8 novembre 2013
  Arash HABIBI
  Mandelbrot.c
\*====================================================*/

#include "Mandelbrot.h"

//-------------------------------------------------------

Mandelbrot* MB_new(int width, int height)
{
	Mandelbrot *mb;
	mb = (Mandelbrot*)malloc(sizeof(Mandelbrot));
	mb->_width = width;
	mb->_height = height;
	mb->_zoom_val = 1;
	mb->_zoom = CX_new(0,0);
	mb->_offset = CX_new(0,0);
	mb->_iteration_max = 255;
	mb->_threshold = 4.0;
	mb->_zmin = CX_new(-2.25,-1.25);
	mb->_zmax = CX_new( 0.75, 1.25);

	return mb;
}

//-------------------------------------------------------

static void _windowToImage(Mandelbrot *mb, int xwin, int ywin, scalar *ximg, scalar *yimg)
{
	*ximg = mb->_zoom._real + mb->_offset._real + (xwin-mb->_zoom._real) / mb->_zoom_val;
	*yimg = mb->_zoom._imgn + mb->_offset._imgn + (ywin-mb->_zoom._imgn) / mb->_zoom_val;
}

//-------------------------------------------------------

static Complex _imageToComplex(Mandelbrot *mb, scalar ximg, scalar yimg)
{
	scalar realz = mb->_zmin._real + ximg*(mb->_zmax._real-mb->_zmin._real)/(mb->_width-1);
	scalar imgnz = mb->_zmin._imgn + yimg*(mb->_zmax._imgn-mb->_zmin._imgn)/(mb->_height-1);

	return CX_new( realz, imgnz);
}

//-------------------------------------------------------

void MB_check(Mandelbrot *mb, char *message)
{
	fprintf(stderr,"------------- Check Mandelbrot %s ------------------\n",message);
	fprintf(stderr,"%d x %d pixels.\n",mb->_width,mb->_height);
	CX_check(mb->_zoom,"Centre de zoom : ");
	fprintf(stderr,"Facteur de zoom : %f\n",mb->_zoom_val);
	CX_check(mb->_offset,"Décalage : ");

	fprintf(stderr,"Les quatre coins de la fenêtre : \n");
	scalar ximg, yimg;
	_windowToImage(mb,0,0,&ximg,&yimg);
	fprintf(stderr,"0,0 -> ximg=%f yimg=%f\n",ximg,yimg);

	_windowToImage(mb,mb->_width-1,0,&ximg,&yimg);
	fprintf(stderr,"%d,0 -> ximg=%f yimg=%f\n",mb->_width-1,ximg,yimg);

	_windowToImage(mb,0,mb->_height-1,&ximg,&yimg);
	fprintf(stderr,"0,%d -> ximg=%f yimg=%f\n",mb->_height-1,ximg,yimg);

	_windowToImage(mb,mb->_width-1,mb->_height-1,&ximg,&yimg);
	fprintf(stderr,"%d,%d -> ximg=%f yimg=%f\n",mb->_width-1,mb->_height-1,ximg,yimg);
}

//-------------------------------------------------------

static Complex _oneIteration(Complex z, Complex z0)
{
	return CX_add(z0,CX_square(z));
}

//-------------------------------------------------------

static int _nbIterations(Mandelbrot *mb, Complex z0)
{
	int count=0;
	Complex z;

	z = z0;

	while((count++ < mb->_iteration_max)&&
		  (CX_squareModule(z)<mb->_threshold))
		z = _oneIteration(z, z0);

  return(count);
}

//-------------------------------------------------------

extern int MB_compute(Mandelbrot *mb, int xwin, int ywin)
{
	if((xwin==0)&&(ywin==0))
		MB_check(mb,"Dans MB_compute");

	scalar ximg, yimg;
	_windowToImage(mb, xwin, ywin, &ximg, &yimg);
	Complex z0 = _imageToComplex(mb, ximg, yimg);
	return _nbIterations(mb,z0);
}

//-------------------------------------------------------

void MB_focusPoint(Mandelbrot *mb, int xwin, int ywin)
{
	int dx = xwin - mb->_zoom._real;
	int dy = ywin - mb->_zoom._imgn;
	mb->_offset._real += dx*(1.0/mb->_zoom_val-1);
	mb->_offset._imgn += dy*(1.0/mb->_zoom_val-1);
	mb->_zoom._real = xwin;
	mb->_zoom._imgn = ywin;
}

//-------------------------------------------------------

void MB_zoomInit(Mandelbrot *mb)
{
	mb->_offset = CX_new(0,0);
	mb->_zoom   = CX_new(0,0);
	mb->_zoom_val = 1.0;
}

//-------------------------------------------------------

void MB_zoom(Mandelbrot *mb, scalar zoom_coef)
{
	mb->_zoom_val = mb->_zoom_val * zoom_coef;
}

//-------------------------------------------------------

void MB_move(Mandelbrot *mb, int x, int y)
{
	mb->_offset._real += x;
	mb->_offset._imgn += y;
}

//-------------------------------------------------------
