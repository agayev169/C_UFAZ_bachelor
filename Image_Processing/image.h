#include <stdio.h>
#include "color.h"

void I_replace (Color *temp, Color *img, int nb_pixels);
void I_print (Color *img, int nb_pixels);
void I_coef (Color *img, int nb_pixels, float coef);
void I_negative (Color *img, int nb_pixels);
void I_permute (Color *img, int nb_pixels);
void I_grayScale (Color *img, int nb_pixels);
void I_grayScaleCoef (Color *img, int nb_pixels);
void I_thershold (Color *img, int nb_pixels, int th);
void I_addColor (Color *img, int nb_pixels, Color c);
void I_gradient (Color *img_in, Color *img_out, int nb_pixels);
void I_compose (Color *img1, Color *img2, int nb_pixels, Color target);
Color I_average (Color *img, int nb_pixels, int fromhere, int nb_pixels_average);
void I_motionBlur (Color *img, Color *img_out, int nb_pixels, int strength);
void I_flipX (Color *img, int width, int height);// Additional function
void I_flipY (Color *img, int width, int height);// Additional function
void I_mirrorRight (Color *img, int width, int height);// Additional function
void I_mirrorLeft (Color *img, int width, int height);// Additional function
void I_saturation (Color *img, int nb_pixels, float coef);
double I_getSaturation (Color *img, int nb_pixels);
void I_addWhite (Color *img, int nb_pixels, float coef);
void I_addBlack (Color *img, int nb_pixels, float coef);
void I_addTint (Color *img, int nb_pixels, int col, float coef);
void I_addHighlights (Color *img, int nb_pixels, float coef);
