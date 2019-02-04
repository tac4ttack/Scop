// TGA.cpp: implementation of the TGA class.
//
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TGA.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TGA::TGA()
{
	image = new unsigned char[3];
	height = 1;
	width = 1;
	bpp = 24;
}

TGA::~TGA()
{
	delete image;
}

bool TGA::load(char *filePath)
{
	unsigned short awidth = 0, aheight = 0;			// taille de l'image (utilisé pour lire dans le fichier)
	unsigned char length = 0;					// taille entre l'entete et les pixels
	unsigned char imageType = 0;					// type de l'image (RLE, RGB, Alpha...)
	unsigned char bits = 0;						// bit par pixel de l'image (16, 24, 32)
	FILE *pFile = NULL;					// fichier
	int channels = 0;					// nombre de channels de l'image (3 = RGA : 4 = RGBA)
	int stride = 0;						// longeure d'une ligne
	int i = 0;							// ;-)
		
	if((pFile = fopen(filePath, "rb")) == NULL) 
	{
		fprintf(stderr,"impossible d'ouvrire le fichier TGA %s\n",filePath);
		fclose(pFile);
		return false;
	}
		
	// lit la distance entre l'entete du fichier et les pixels
	fread(&length, sizeof(unsigned char), 1, pFile);
	
	// passe 1 octet (pourquoi ?)
	fseek(pFile,1,SEEK_CUR); 

	// lit le type de l'image
	fread(&imageType, sizeof(unsigned char), 1, pFile);
	
	// passe des info sans importance
	fseek(pFile, 9, SEEK_CUR); 

	// lit les info de l'image
	fread(&awidth,  sizeof(unsigned short), 1, pFile);
	fread(&aheight, sizeof(unsigned short), 1, pFile);
	fread(&bits,   sizeof(unsigned char), 1, pFile);
	
	// on sauvegarde dans les attributs de la classe
	width = awidth;
	height = aheight;
	// sauvegarde le nombre de bpp
	this->bpp = bits;

	// on passe au info des pixels
	fseek(pFile, length + 1, SEEK_CUR); 

	// verifie le type de l'image (RGB, RLE )
	if(imageType != TGA_RLE)
	{
		// image 24 ou 32 bits ?
		if(bits == 24 || bits == 32)
		{
			// calcule le nombre de channels de l'image
			channels = bits / 8;
			// calcule la longeur d'une ligne de pixels
			stride = channels * width;
			// alloue la memoire pour l'image
			delete image;
			image = new unsigned char[stride * height];

			// charge tout les pixels ligne par ligne
			for(int y = 0; y < height; y++)
			{
				// pointeur sur le ligne courante de pixels
				unsigned char *line = &(image[stride * y]);

				// lit la ligne de pixels
				fread(line, stride, 1, pFile);
			
				// passe de BGR (type des TGA) a RGB (utilisé par openGL)
				for(i = 0; i < stride; i += channels)
				{
					int temp     = line[i];
					line[i]      = line[i + 2];
					line[i + 2]  = temp;
				}
			}
		}
		// regarde si c'est une image 16 bits (info de couleurs stocké sur 2 unsigned char)
		else if(bits == 16)
		{
			unsigned short pixels = 0;
			int r=0, g=0, b=0;

			// on force le passage sur 3 channels
			channels = 3;
			// on calcule la longeur d'une ligne
			stride = channels * width;
			// on alloue la memoire pour l'image
			delete image;
			image = new unsigned char[stride * height];

			// on charge le pixels pixel par pixel
			for(int i = 0; i < width*height; i++)
			{
				// lecture du pixel courant
				fread(&pixels, sizeof(unsigned short), 1, pFile);
				
				// passage de 16 bit en 24 bits (on lit les composante RGB contenu dans 1
				// octet grace a des operaion bit a bit...
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;
				
				// assigne les couleur (en en profitant pour swaper de BGR a RGB)
				image[i * 3 + 0] = r;
				image[i * 3 + 1] = g;
				image[i * 3 + 2] = b;
			}
			// maintenant on a une image en 24 bpp
			bits = 24;
		}	
		// sinon, c'est un format de pixels inconnus
		else
		{
			fprintf(stderr, "impossible de lire le fichier TGA %s : format de pixel inconnu\n", filePath);
			fclose(pFile);
			return false;
		}
	}
	// analyse de TGA compressé
	else
	{

		// variables utilisée pour la decompression
		unsigned char rleID = 0;
		int colorsRead = 0;
		channels = bits / 8;
		stride = channels * width;

		//allocation de la memoire
		delete image;
		image = new unsigned char[stride * height];
		// creation d'un tableau de couleur temporaire
		unsigned char *colors = new unsigned char [channels];

		// chargement des info de pixel
		while(i < width*height)
		{
			// lecture du color count
			fread(&rleID, sizeof(unsigned char), 1, pFile);
			
			// on verifie que ce ne sont pas des donnée compressé
			if(rleID < 128)
			{
				// augmente le nombre de couleurs  lire de 1
				rleID++;

				// lit toute les couleurs non compresé a se suivre
				while(rleID)
				{
					// lit la couleur courante
					fread(colors, sizeof(unsigned char) * channels, 1, pFile);

					// sauvegarde la couleur dans le tableau
					image[colorsRead + 0] = colors[2];
					image[colorsRead + 1] = colors[1];
					image[colorsRead + 2] = colors[0];

					// si on est en 24 bits, alors on ajoute un cannal alpha
					if(bits == 32)
						image[colorsRead + 3] = colors[3];

					i++;
					rleID--;
					colorsRead += channels;
				}
			}
			// on est en train de lire une chaine de couleur compressé
			else
			{
				// on enleve 127 pour connaitre le nombre de couleurs a lire
				rleID -= 127;

				// lit la couleur courante
				fread(colors, sizeof(unsigned char) * channels, 1, pFile);

				// lit les pixels identiques
				while(rleID)
				{
					// sauvegarde l'info dans le tableau de l'image
					image[colorsRead + 0] = colors[2];
					image[colorsRead + 1] = colors[1];
					image[colorsRead + 2] = colors[0];

					// si on est en 32 bits, on ajoute le canal alpha
					if(bits == 32)
						image[colorsRead + 3] = colors[3];

					i++;
					rleID--;
					colorsRead += channels;
				}
				
			}
				
		}
	}

	// ferme le fichier
	fclose(pFile);	
	return true;

}