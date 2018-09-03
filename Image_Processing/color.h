#ifndef BLAH
#define BLAH

#define RED 0
#define GREEN 1
#define BLUE 2

typedef struct {
	int red, green, blue;
} Color;

void C_print (Color c);
Color C_new (int red, int green, int blue);
int clamp (int n);
Color C_multiply (Color c, float coef);
Color C_negative (Color c);
Color C_permute (Color c);
int C_intensity (Color c);
Color C_grayScale (Color c);
Color C_grayScaleCoef (Color c);
int C_thershold (Color c, int th);
Color C_th (Color c, int th);
int C_areEqual (Color c1, Color c2);
Color C_replace (Color c);
Color C_addCoef (Color c1, Color c2, float coef);
Color C_gradient (Color c1, Color c2);
Color C_saturation (Color c, float coef);
int C_getSaturation (Color c);
Color C_addWhite (Color c, float coef);
Color C_addBlack (Color c, float coef);
Color C_addTint (Color c, int col, float coef);
Color C_addHighlights (Color c, float coef);

#endif
