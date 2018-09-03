
/*=====================================================*\
  Mercredi 29 mai 2013
  Arash HABIBI
  Ppm.c

  Algorithme de lecture :

  mode : magic_pas_lu
       alors lu : interprete comme un bout de magique jusqu'à :
	   espace ->espace ou commentaire
	   espace -> mode espace
	   commentaire -> mode commentaire


\*=====================================================*/

#include "Ppm.h"

//------------------------------------------------------

static int _lectureEntete(Ppm ppm)
{
	int diagnost=PPM_OK;
	int largeur_lue=0;
	int hauteur_lue=0;
	int val_max_lue=0;
	int entier=0;

	int mode = PPM_LECTURE_MAGIC;
	int indice_magic=0;
	ppm->_magic[0]='\0';

	while(! val_max_lue)
	{
		int lu=fgetc(ppm->_ppmfile);

		switch(mode)
		{
			//--------

		case PPM_LECTURE_MAGIC :
			if(lu=='#')
			{
				mode=PPM_LECTURE_COMMENTAIRE;
				ppm->_magic[indice_magic++]='\0';
			}
			else if(isspace(lu))
			{
				mode=PPM_LECTURE_ESPACE;
				ppm->_magic[indice_magic++]='\0';
			}
			else
				ppm->_magic[indice_magic++]=lu;
			break;

			//--------

		case PPM_LECTURE_COMMENTAIRE :
			if(lu=='\n')
				mode=PPM_LECTURE_ESPACE;
			break;

			//--------

		case PPM_LECTURE_ESPACE :

			if(! isspace(lu))
			{
				if(lu=='#')
					mode=PPM_LECTURE_COMMENTAIRE;

				else if(isdigit(lu))
				{
					if( !largeur_lue || !hauteur_lue || !val_max_lue )
					{
						entier=lu-'0';
						mode=PPM_LECTURE_NOMBRE;
					}
					else
						ungetc(lu,ppm->_ppmfile); // certainement les premières données à lire
				}
				else
				{
					fprintf(stderr,"_lectureEntete : ERREUR ! \n");
					fprintf(stderr,"Que fait le caractère \'%c\' dans l'entete d'un fichier ppm ?\n",lu);
					diagnost=PPM_ERROR;
					mode=PPM_ERROR;
				}
			}
			break;

			//--------

		case PPM_LECTURE_NOMBRE :

			if(isdigit(lu))
				entier = 10*entier + (lu-'0');

			else if(lu=='#')
				mode=PPM_LECTURE_COMMENTAIRE;

			else if(isspace(lu))
					mode=PPM_LECTURE_ESPACE;

			else
			{
				fprintf(stderr,"_lectureEntete : ERREUR ! \n");
				fprintf(stderr,"Que fait le caractère \'%c\' dans l'entete d'un fichier ppm ?\n",lu);
				diagnost=PPM_ERROR;
				mode=PPM_ERROR;
			}

			if(mode!=PPM_LECTURE_NOMBRE)
			{
				if(largeur_lue==0)
				{ ppm->_largeur = entier; largeur_lue=1; }

				else if(hauteur_lue==0)
				{ ppm->_hauteur = entier; hauteur_lue=1; }

				else // if(val_max_lue==0)
				{ ppm->_valmax   = entier; val_max_lue=1; }

				entier=0;
			}
			break;

			//--------

		default :
			fprintf(stderr,"_lectureEntete : ERROR.\n");
			fprintf(stderr,"mode %d inconnu.\n",mode);
			diagnost=PPM_ERROR;
			break;
		}
	}
	return(diagnost);
}

//------------------------------------------------------

static void _ecritureEntete(Ppm ppm)
{
	if((ppm->_largeur==-1)||(ppm->_hauteur==-1)||
	   (ppm->_valmax==-1) ||(ppm->_type==-1)||
	   (ppm->_nb_bytes==-1))
	{
		fprintf(stderr,"_ecritureEntete : ERREUR !\n");
		fprintf(stderr,"ppm n'a pas ete initialise pour l'ecriture.\n");
		fprintf(stderr,"On ne connait ni la largeur, ni la hauteur ...\n");
		exit(1);
	}
	else
	{
		if(PPM_estBinaire(ppm))	fprintf(ppm->_ppmfile,"P6\n");
		else					fprintf(ppm->_ppmfile,"P3\n");

		fprintf(ppm->_ppmfile,"%d %d\n%d\n",ppm->_largeur, ppm->_hauteur,ppm->_valmax);
	}
}

//------------------------------------------------------

Ppm PPM_nouv(char *ppmfilename, int lecture_ecriture)
{
	Ppm ppm;

	ppm = (Ppm)malloc(sizeof(StructPpm));

	strcpy(ppm->_ppmfilename,ppmfilename);

	if(lecture_ecriture==PPM_LECTURE)	ppm->_ppmfile=fopen(ppmfilename,"r");
	else								ppm->_ppmfile=fopen(ppmfilename,"w");
	if(ppm->_ppmfile==NULL)
	{
		perror(ppmfilename);
		free(ppm);
		return(NULL);
	}
	else
	{
		if(lecture_ecriture==PPM_LECTURE)
		{
			int res=_lectureEntete(ppm);

			if(res==PPM_OK)
			{
				if(strcmp(ppm->_magic,"P3")==0)
					ppm->_type=PPM_ASCII;

				else if(strcmp(ppm->_magic,"P6")==0)
					ppm->_type=PPM_BINAIRE;

				else
				{
					fprintf(stderr,"PPM_nouv : ERREUR !\n");
					fprintf(stderr,"Le fichier %s ne semble pas etre un fichier PPM (%s).\n",
							ppmfilename,ppm->_magic);
					free(ppm);
					return(NULL);
				}

				if(ppm->_valmax < 256)
					ppm->_nb_bytes=1;
				else
					ppm->_nb_bytes=2;

			}
		}
		else
		{
			ppm->_type=-1;
			ppm->_nb_bytes=-1;
			ppm->_largeur=-1;
			ppm->_hauteur=-1;
			ppm->_valmax=-1;
		}
	}
	return(ppm);
}

//------------------------------------------------------

void PPM_initEcriture(Ppm ppm, int type, int largeur, int hauteur, int nb_bytes)
{
	ppm->_type    = type;
	ppm->_largeur = largeur;
	ppm->_hauteur = hauteur;
	ppm->_nb_bytes= nb_bytes;

	if(nb_bytes<=1)	ppm->_valmax = 255;
	else		   	ppm->_valmax = 65535;

	_ecritureEntete(ppm);
}

//------------------------------------------------------

void PPM_check(Ppm ppm, char *message)
{
	fprintf(stderr,"------------------ check Ppm %s -----------------------\n",message);
	if(PPM_estBinaire(ppm))
		fprintf(stderr,"Fichier binaire.\n");
	else
		fprintf(stderr,"Fichier ascii.\n");

	fprintf(stderr,"Dimensions : %d x %d \n", ppm->_largeur, ppm->_hauteur);
	fprintf(stderr,"Chaque pixel a 3 composantes ayant chacune %d bytes (valmax=%d)\n",
			ppm->_nb_bytes,ppm->_valmax);
	fprintf(stderr,"\n");
}

//------------------------------------------------------

int PPM_largeur(Ppm ppm)
{
	return(ppm->_largeur);
}

//------------------------------------------------------

int PPM_hauteur(Ppm ppm)
{
	return(ppm->_hauteur);
}

//------------------------------------------------------

int PPM_valmax(Ppm ppm)
{
	return(ppm->_valmax);
}

//------------------------------------------------------

int PPM_nbBytes(Ppm ppm)
{
	return(ppm->_nb_bytes);
}

//------------------------------------------------------

int PPM_estBinaire(Ppm ppm)
{
	return(ppm->_type==PPM_BINAIRE);
}

//------------------------------------------------------

int PPM_nbPixels(Ppm ppm)
{
	return(ppm->_largeur * ppm->_hauteur);
}

//------------------------------------------------------

void PPM_lectureDonneesChar(Ppm ppm, unsigned char *donnees)
{
	int nb_donnees=3*ppm->_largeur*ppm->_hauteur;
	int nb_lu=0;
	unsigned char entier=0;

	if(PPM_estBinaire(ppm))
	{
		nb_lu=fread(donnees,ppm->_nb_bytes,nb_donnees,ppm->_ppmfile);
		if(nb_lu==nb_donnees)
			; // fprintf(stderr,"Lecteur PPM : tout va bien.\n");
		else
			fprintf(stderr,"Lecteur PPM : %d chiffres lus %d attendus.\n",nb_lu,nb_donnees);
	}
	else
	{
		int lu, fini=0;
		int commentaire=0;
		while(!fini)
		{
			lu = fgetc(ppm->_ppmfile);

			if(lu==EOF)
				fini=1;

			else if(! commentaire)
			{
				if(lu=='#')
					commentaire=1;

				else if(isdigit(lu))
					entier=10*entier + lu;

				else if(isspace(lu))
				{
					if((commentaire)&&(lu=='\n'))
						commentaire=0;
					else
					{
						donnees[nb_lu]=entier;
						nb_lu++;
						entier=0;
					}
				}
				if(nb_lu>=nb_donnees)
					fini=1;
			}
		}
		if((lu==EOF)&&(nb_lu==nb_donnees))
			fprintf(stderr,"Lecteur PPM : tout va bien.\n");

		else if(nb_lu==nb_donnees)
			fprintf(stderr,"Lecteur PPM : il reste encore des choses à lire.\n");

		else // if(lu==EOF)
			fprintf(stderr,"Lecteur PPM : fin de fichier rencontre avant que les donnees soient toutes lues.\n");
	}
}

//------------------------------------------------------

void PPM_lectureDonneesShort(Ppm ppm, unsigned short *donnees)
{
	int nb_donnees=3*ppm->_largeur*ppm->_hauteur;
	int nb_lu=0;
	unsigned short entier=0;

	if(PPM_estBinaire(ppm))
	{
		nb_lu=fread(donnees,ppm->_nb_bytes,nb_donnees,ppm->_ppmfile);
		if(nb_lu==nb_donnees)
			fprintf(stderr,"Lecteur PPM : tout va bien.\n");
		else
			fprintf(stderr,"Lecteur PPM : %d chiffres lus %d attendus.\n",nb_lu,nb_donnees);
	}
	else
	{
		int lu, fini=0;
		int commentaire=0;
		while(!fini)
		{
			lu = fgetc(ppm->_ppmfile);

			if(lu==EOF)
				fini=1;

			else if(! commentaire)
			{
				if(lu=='#')
					commentaire=1;

				else if(isdigit(lu))
					entier=10*entier + lu;

				else if(isspace(lu))
				{
					if((commentaire)&&(lu=='\n'))
						commentaire=0;
					else
					{
						donnees[nb_lu]=entier;
						nb_lu++;
						entier=0;
					}
				}
				if(nb_lu>=nb_donnees)
					fini=1;
			}
		}
		if((lu==EOF)&&(nb_lu==nb_donnees))
			fprintf(stderr,"Lecteur PPM : tout va bien.\n");

		else if(nb_lu==nb_donnees)
			fprintf(stderr,"Lecteur PPM : il reste encore des choses à lire.\n");

		else // if(lu==EOF)
			fprintf(stderr,"Lecteur PPM : fin de fichier rencontre avant que les donnees soient toutes lues.\n");
	}
}

//------------------------------------------------------

void PPM_ecritureDonneesChar(Ppm ppm, unsigned char *donnees)
{
	int nb_donnees=3*ppm->_largeur*ppm->_hauteur;

	if(PPM_estBinaire(ppm))
		fwrite(donnees,ppm->_nb_bytes,nb_donnees,ppm->_ppmfile);
	else
	{
		int n;
		for(n=0;n<nb_donnees;n++)
			fprintf(ppm->_ppmfile,"%d ",donnees[n]);
	}
}

//------------------------------------------------------

void PPM_ecritureDonneesShort(Ppm ppm, unsigned short *donnees)
{
	int nb_donnees=3*ppm->_largeur*ppm->_hauteur;

	if(PPM_estBinaire(ppm))
		fwrite(donnees,ppm->_nb_bytes,nb_donnees,ppm->_ppmfile);
	else
	{
		int n;
		for(n=0;n<nb_donnees;n++)
			fprintf(ppm->_ppmfile,"%d ",donnees[n]);
	}
}

//------------------------------------------------------

void PPM_fermeture(Ppm ppm)
{
	fclose(ppm->_ppmfile);
	free(ppm);
}

