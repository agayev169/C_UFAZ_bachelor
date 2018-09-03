#include <stdio.h>
#include "color.h"

void C_print (Color c) {
	printf("(%d, %d, %d)\n", c.red, c.green, c.blue);
}

Color C_new (int red, int green, int blue) {
	Color tempColor = {red, green, blue};
	return tempColor;
}

int clamp (int n) {
	if (n < 0) return 0;
	if (n > 255) return 255;
	return n;
}

Color C_multiply (Color c, float coef) {
	if (coef > 0) {
		c.red = clamp (c.red * coef);
		c.green = clamp (c.green * coef);
		c.blue = clamp (c.blue * coef);
	}
	return c;
}

Color C_negative (Color c) {
	c.red = 255 - c.red;
	c.green = 255 - c.green;
	c.blue = 255 - c.blue;
	return c;
}

Color C_permute (Color c) {
	int temp = c.red;
	c.red = c.blue;
	c.blue = c.green;
	c.green = temp;
	return c;
}

int C_intensity (Color c) {
	return (c.red + c.green + c.blue) / 3;
}

Color C_grayScale (Color c) {
	c.red = c.green = c.blue = C_intensity (c);
	return c;
}

int C_intensityCoef (Color c) {//Additional function. We don't need it I was just testing some stuff
	return (c.red * 0.299 + c.green * 0.587 + c.blue * 0.114);
}

Color C_grayScaleCoef (Color c) {
	c.red = c.green = c.blue = C_intensityCoef (c);
	return c;
}

int C_thershold (Color c, int th) {
	if (C_intensity(c) > th) return 255;
	return 0;
}

Color C_th (Color c, int th) {//In pdf they didn't mention this function but we need it. It just assigns the output of C_thershold function(0 or 1) to all values(red, green and blue) of pixel
	c.red = c.green = c.blue = C_thershold (c, th);
	return c;
}

int C_areEqual (Color c1, Color c2) {
	if (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue) return 1;
	return 0;
}

Color C_replace (Color c) {//Additional function. We need it for temprorary variable in our main function but you can also solve this problem another way(Read about this in main.c file)
	Color temp;
	temp.red = c.red;
	temp.green = c.green;
	temp.blue = c.blue;
	return temp;
}

Color C_addCoef (Color c1, Color c2, float coef) {
	Color temp;
	temp.red = clamp(c1.red + coef * c2.red);
	temp.green = clamp(c1.green + coef * c2.green);
	temp.blue = clamp(c1.blue + coef * c2.blue);
	return temp;
}

Color C_gradient (Color c1, Color c2) {
	const int gray = 127;//defining gray color
	Color temp;
	temp.red = clamp(c2.red - c1.red + gray);//calculating new value of red color and clamping it to be sure that it is in our range
	temp.green = clamp(c2.green - c1.green + gray);//calculating new value of green color and clamping it to be sure that it is in our range
	temp.blue = clamp(c2.blue - c1.blue + gray);//calculating new value of blue color and clamping it to be sure that it is in our range
	return temp;
}
