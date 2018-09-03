#include "image.h"

void I_replace (Color *temp, Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) temp[i] = C_replace(img[i]);
}

void I_print (Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) C_print (img[i]);
}

void I_coef (Color *img, int nb_pixels, float coef) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_multiply (img[i], coef);
}

void I_negative (Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_negative (img[i]);
}

void I_permute (Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_permute (img[i]);
}

void I_grayScale (Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_grayScale (img[i]);
}

void I_grayScaleCoef (Color *img, int nb_pixels) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_grayScaleCoef (img[i]);
}

void I_thershold (Color *img, int nb_pixels, int th) {
	for (int i = 0; i < nb_pixels; i++) img [i] = C_th (img[i], th);
}

void I_compose (Color *img1, Color *img2, int nb_pixels, Color target) {
	for (int i = 0; i < nb_pixels; i++) if (C_areEqual(img1[i], target)) img1[i] = C_replace(img2[i]);//Replacing the pixel of image if its value is same compared to the target color's value
}

void I_addColor (Color *img, int nb_pixels, Color c) {
	for (int i = 0; i < nb_pixels; i++) img[i] = C_addCoef (img[i], c, 1);
}

void I_gradient (Color *img_in, Color *img_out, int nb_pixels) {
	img_out[0] = C_new (127, 127, 127);//Assigning gray color to 1st pixel of output image 
	for (int i = 0; i < nb_pixels; i++) 
		img_out[i] = C_gradient (img_in[i-1], img_in[i]);//Calling gradient function for each pair of pixels of input image
}

Color I_average (Color *img, int nb_pixels, int fromhere, int nb_pixels_average) {
	int lastpx = fromhere + nb_pixels_average - 1;//Declaring and defining the last pixel of image that we will get to change
	//Note that it's not the last pixel of image but the last pixel that we will change in our image
	Color avg = C_new(0, 0, 0);//Declaring the variable that will hold our value and defining it as black value
	//We use black value because its red, green and blue values are zeros so it doesn't change anything if we add it to any pixel(The color will not change)
	if (lastpx < nb_pixels && fromhere >= 0) { //Checking if last pixels and first pixel is inside our image 
		for (int i = fromhere; i <= lastpx; i++) {
			avg.red += img[i].red;//Adding red component of current pixel to the variable average 
			avg.green += img[i].green;//Adding green component of current pixel to the variable average 
			avg.blue += img[i].blue;//Adding blue component of current pixel to the variable average 
		}
	}
	avg.red /= nb_pixels_average;//Till now avg was just a sum of red color of pixels from "fromhere" to "lastpx" so now we are calculating the average of each color inside our function
	avg.green /= nb_pixels_average;//Till now avg was just a sum of green color of pixels from "fromhere" to "lastpx" so now we are calculating the average of each color inside our function
	avg.blue /= nb_pixels_average;//Till now avg was just a sum of blue color of pixels from "fromhere" to "lastpx" so now we are calculating the average of each color inside our function
	
	return avg;
}

void I_motionBlur (Color *img, Color *img_out, int nb_pixels, int strength) {
	for (int i = 0; i < nb_pixels - strength; i++) img_out[i] = I_average(img, nb_pixels, i, strength);//Calling the I_average funtion for each "strength"s pixels(strength is a number of pixels) pf image to find the average of their value
}

void I_flipX (Color *img, int width, int height) {// Additional function. We don't have it in PW01 I added it myself so you don't need it.
	Color temp;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width/2; j++) {
			temp = C_replace (img[width * i + j]);
			img[width * i + j] = C_replace (img[width * (i + 1) - j - 1]);
			img[width * (i + 1) - j - 1] = C_replace (temp);
		}
	}
}

void I_flipY (Color *img, int width, int height) {// Additional function. We don't have it in PW01 I added it myself so you don't need it.
	Color temp;
	for (int i = 0; i < width/2; i++) {
		for (int j = 0; j < height; j++) {
			temp = C_replace (img[width * i + j]);
			img[width * i + j] = C_replace (img[width * (height - i - 1) + j]);
			img[width * (height - i - 1) + j] = C_replace (temp);
		}
	}
}

void I_mirrorRight (Color *img, int width, int height) {// Additional function. We don't have it in PW01 I added it myself so you don't need it.
	Color temp;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img[width * i + j] = C_replace (img[width * (i + 1) - j - 1]);
}

void I_mirrorLeft (Color *img, int width, int height) {// Additional function// Additional function. We don't have it in PW01 I added it myself so you don't need it.
	Color temp;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img[width * (i + 1) - j - 1] = C_replace (img[width * i + j]);
}
