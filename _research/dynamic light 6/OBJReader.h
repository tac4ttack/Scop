// OBJReader.h: interface for the OBJReader class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OBJREADER_H
#define OBJREADER_H

#include <vector>
#include <string>

/**
 * classe permettant de chargement d'un fichier au format .obj.
 * cette classe prend en compte les fichier .obj avec ou sans normal et coordonnée de textures.
 * Par contre, elle ne prend en compte que les fichier .obj triangulé.
 */
class OBJReader  
{
public:
	/**
	 * structure definissant un vecteur 3D
	 */
	struct OBJVector
	{
		float x,y,z;
	};
	/**
	 * structure definissant des coordonnée de texture 2D
	 */
	struct OBJtexCoord
	{
		float u,v;
	};
	/**
	 * structure definissant les index vers les informations utilisé par les faces
	 */
	struct OBJface
	{
		int vertex[3];
		int normal[3];
		int texture[3];
	};

private:
	/**
	 * le nom du fichier à charger
	 */
	std::string file;
	/**
	 * le fichier à charger
	 */
	FILE * fichier;
	/**
	 * booleen permettant de savoir si le fichier contient des informations de texture ou pas
	 */
	bool useTex;
	/**
	 * booleen permettant de savoir si le fichier contint des informations sur les normales ou pas.
	 */
	bool useNorm;
	/**
	 * fonction utilisée pour lire une face dans le fichier
	 */
	void readFace();
	/**
	 * fonction utilisée pour lire une coordonnée de texture dans le fichier
	 */
	void readTexture();
	/**
	 * fonction utilisé pour lire une normal dans le fichier
	 */
	void readNormal();
	/**
	 * fonction utilisée pour lire un vertex dans le fichier
	 */
	void readVertex();
protected:
	/**
	 * vecteur contenant les vertex du model
	 */
	std::vector <OBJVector> vertex;
	/**
	 * vecteur contenant les normals du model
	 */
	std::vector <OBJVector> normal;
	/**
	 * vecteur contenant les coordonnée de texture du model
	 */
	std::vector <OBJtexCoord> texture;
	/**
	 * vecteur contenant les faces du model
	 */
	std::vector <OBJface> face;

public:
	/**
	 * constructeur d'obj reader prenant en parametre le chemin du fichier contenant le model
	 * @param fichier : le chemin du fichier contenant le model
	 */
	OBJReader(std::string fichier);
	/**
	 * constructeur par defaut
	 */
	OBJReader();
	/**
	 * destructeur
	 */
	virtual ~OBJReader();
	/**
	 * methode permettant d'afficher le resultat du model dans un fichier au format .obj
	 * @param fichier : le fichier dans lequel ecrire 
	 */
	void print(FILE * fichier = stdout);
	/**
	 * methode permettant de charger le model.
	 * @return bool : true si le chargement c'est bien passé, false sinon.
	 */
	bool load();
	
	/**
	 * methode permettant de changer le nom du fichier à charger
	 */
	inline void setFile(std::string aFile){file = aFile;};
	/**
	 * methode permettant de recuperer le nom du fichier contenant le model.
	 * @return std::string : le nom du fichier contenant le model
	 */
	inline std::string getFile(){return file;};
	/**
	 * methode permettant de recuperer le vecteur contenant les vertex du model
	 * @return std::vector<OBJVector> : le vecteur contenant les vertex du model
	 */
	inline std::vector<OBJVector> & getVertex(){return vertex;};
	/**
	 * methode permettant de recuperer le vecteur contenant les normals du model
	 * @return std::vector<OBJVector> : le vecteur contenant les normals du model
	 */
	inline std::vector<OBJVector> & getNormal(){return normal;};
	/**
	 * methode permettant de recuperer le vecteur contenant les coordonnée de textures du model
	 * @return std::vector<OBJtexCoord> : le vecteur contenant les coordonnée de textures du model
	 */
	inline std::vector<OBJtexCoord> & getTexture(){return texture;};
	/**
	 * methode permettant de recuperer le vecteur contenant les faces du model
	 * @return std::vector<OBJface> : le vecteur contenant les faces du model
	 */
	inline std::vector<OBJface> & getFace(){return face;};
	/**
	 * methode permettant de savoir si le fichier contient des informations de normals ou pas
	 * @return bool : true si le fichier contient les normales du model, false sinon
	 */
	inline bool useNormal(){return useNorm;};
	/**
	 * methode permettant de savoir si le fichier contient des informations de coordonnée de textures ou pas.
	 * @return bool : true si le fichier contient des coordonnée de textures, false sinon.
	 */
	inline bool useTexturing(){return useTex;};

};

#endif
