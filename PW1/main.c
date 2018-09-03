#include <stdio.h>
#include "color.h"
#include "image.h"
#include "ppm.h"
#define WIDTH 605//You don't need this. I needed it to work with additional functions
#define HEIGHT 600//You don't need this. I needed it to work with additional functions

int main () {
	Color *img;
	int nbpixels;
	struct ppm p;

	p = PPM_new("merida.ppm");
	nbpixels = PPM_nbPixels(p);
	img = PPM_pixels(p);
	Color temp[nbpixels];//The temprorary variable that will keep our image. We need it not to change the initial image but work with this variable and even if we change it we can call I_replace to assign the image to this variable
	//So I will call I_replace each time before next function to assign the image to our temp variable. Even if it is changed we have the original image in *img

	I_replace(temp, img, nbpixels);
	I_thershold(temp, nbpixels, 127);
	PPM_save(p, temp, "th.ppm");

	I_replace(temp, img, nbpixels);
	I_negative(temp, nbpixels);
	PPM_save(p, temp, "neg.ppm");
	
	I_replace(temp, img, nbpixels);
	I_coef (temp, nbpixels, 1.2);
	PPM_save(p, temp, "coef.ppm");
	
	I_replace(temp, img, nbpixels);
	I_permute (temp, nbpixels);
	PPM_save(p, temp, "permute.ppm");

	I_replace(temp, img, nbpixels);
	I_addColor(temp, nbpixels, C_new(127, 127, 127));
	PPM_save(p, temp, "addcolor.ppm");
	
	I_replace(temp, img, nbpixels);
	I_gradient(img, temp, nbpixels);
	PPM_save(p, temp, "gradient.ppm");
	
	I_replace(temp, img, nbpixels);
	I_motionBlur(img, temp, nbpixels, 15);
	PPM_save(p, temp, "mb2.ppm");
	
	p = PPM_new("forest.ppm");
	nbpixels = PPM_nbPixels(p);
	Color *forest = PPM_pixels(p);

	I_replace(temp, img, nbpixels);
	I_compose(temp, forest, nbpixels, C_new(0, 111, 92));
	PPM_save(p, temp, "comp.ppm");
	
	I_replace(temp, img, nbpixels);
	I_flipX(temp, WIDTH, HEIGHT);
	PPM_save(p, temp, "flipx.ppm");
	
	I_replace(temp, img, nbpixels);
	I_mirrorRight(temp, WIDTH, HEIGHT);
	PPM_save(p, temp, "mirrorRight.ppm");
	
	I_replace(temp, img, nbpixels);
	I_mirrorLeft(temp, WIDTH, HEIGHT);
	PPM_save(p, temp, "mirrorLeft.ppm");

	I_replace(temp, img, nbpixels);
	I_flipY(temp, WIDTH, HEIGHT);
	PPM_save(p, temp, "flipy.ppm");

	I_replace(temp, img, nbpixels);
	I_grayScale(temp, nbpixels);
	PPM_save(p, temp, "gray.ppm");
	
	I_replace(temp, img, nbpixels);
	I_grayScaleCoef(temp, nbpixels);
	PPM_save(p, temp, "grayCoef.ppm");

	I_replace(temp, img, nbpixels);
	I_flipX(temp, WIDTH, HEIGHT);
	I_flipY(temp, WIDTH, HEIGHT);
	PPM_save(p, temp, "flipDiagonal.ppm");

	return 0;
}

