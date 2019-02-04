#ifndef TGA_H
#define TGA_H

// un petit define pour fermer le fichier lors de la lecture des TGA
#define EXIT        {fclose(fichier); return false;}
#define TGA_RGB		 2		// TGA en mode RGB
#define TGA_A		 3		// TGA en mode ALPHA
#define TGA_RLE		10		// TGA compressé en RLE

/**
 * clase gerant le chargement d'une image au format TGA.
 * Cette classe prend en compte le chargement des image au format RGB(A), alpha et RGB(A) compressé.
 */
class TGA
{
private:
	/**
	 * le nombre de bits par pixel de l'image (16,24,32)
	 */
	int bpp;
	/**
	 * la largeur de l'image
	 */
	int width;
	/**
	 * la hauteur de l'image
	 */
	int height;
	/**
	 * pointeur vers le tableau de pixel de l'image
	 */
	unsigned char *image;
protected:
public:
	TGA();
	virtual ~TGA();

	/**
	 * methode permettant de charger une image depuis un fichier
	 * @param filePath : le chemin de l'image à charger
	 * @return bool : true si le chargement c'est bien passé, false sinon
	 */
	bool load(char * filePath);
	/**
	 * methode permettant de recuperer le nombre de bits par pixels de l'image
	 * @return int : le nombre de bits par pixels de l'image (24 => RGB, 32 => RGBA)
	 */
	inline int getBpp(){return bpp;};
	/**
	 * methode permettant de recuperer la largeur de l'image
	 * @return int : la largeur de l'image en pixels
	 */
	inline int getWidth(){return width;};
	/**
	 * methode permettant de recuperer la hauteur de l'image
	 * @return int : la hauteur de l'image en pixels
	 */
	inline int getHeight(){return height;};
	/**
	 * methode permettant de recuperer le pointeur vers les pixels de l'image.
	 * Cette methode est a utiliser avec precaution car elle permet de modifier directement
	 * l'image en memoire.
	 * Elle est fournis ici pour pouvoir envoyer les informations de l'image à openGL.
	 * @return unsigned char * : pointeur vers le tableau de pixels de l'image.
	 */
	inline unsigned char * getDatas(){return image;};
};

#endif 