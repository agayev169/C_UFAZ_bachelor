
/*=====================================================*\
  Mercredi 29 mai 2013
  Arash HABIBI
  Ppm.h
\*=====================================================*/

#ifndef _PPM_H_
#define _PPM_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define PPM_ASCII   0
#define PPM_BINAIRE 1

#define PPM_LECTURE  0
#define PPM_ECRITURE 1

#define PPM_LECTURE_MAGIC       0
#define PPM_LECTURE_NOMBRE      1
#define PPM_LECTURE_ESPACE      2
#define PPM_LECTURE_COMMENTAIRE 3

#define PPM_OK     0
#define PPM_EOF   -1
#define PPM_ERROR -2

#define PPM_MAX_LIGNE 70

typedef struct
{
	char _ppmfilename[100];
	FILE *_ppmfile;

	int _largeur, _hauteur, _valmax;
	char _magic[100];

	int _type;
	int _nb_bytes;
} StructPpm, *Ppm;

Ppm  PPM_nouv(char *ppmfilename, int lecture_ecriture);
void PPM_initEcriture(Ppm ppm, int type, int largeur, int hauteur, int nb_bytes);
void PPM_check(Ppm ppm, char *message);
int PPM_largeur(Ppm ppm);
int PPM_hauteur(Ppm ppm);
int PPM_valmax(Ppm ppm);
int PPM_nbBytes(Ppm ppm);
int PPM_estBinaire(Ppm ppm);
int PPM_nbPixels(Ppm ppm);
void PPM_lectureDonneesChar(Ppm ppm, unsigned char *donnees);
void PPM_lectureDonneesShort(Ppm ppm, unsigned short *donnees);
void PPM_ecritureDonneesChar(Ppm ppm, unsigned char *donnees);
void PPM_ecritureDonneesShort(Ppm ppm, unsigned short *donnees);
void PPM_fermeture(Ppm ppm);

#endif


