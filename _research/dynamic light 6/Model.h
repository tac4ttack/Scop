#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "math.h"

// forward declaration
class Light;

/**
 * structure definissant un vecteur 3D
 */
struct Vecteur
{
	float x,y,z;
	Vecteur(){
		x = y = z = 0.0f;
	}
	Vecteur operator+(const Vecteur& v){
		Vecteur ret;
		ret.x = x + v.x;
		ret.y = y + v.y;
		ret.z = z + v.z;
		return ret;
	}
	Vecteur& operator+=(const Vecteur& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vecteur& operator-=(const Vecteur& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vecteur operator-(const Vecteur& v){
		Vecteur ret;
		ret.x = x - v.x;
		ret.y = y - v.y;
		ret.z = z - v.z;
		return ret;
	}
	Vecteur operator*(float v){
		Vecteur ret;
		ret.x = x*v;
		ret.y = y*v;
		ret.z = z*v;
		return ret;
	}
	float operator*(const Vecteur& v){
		return x*v.x + y*v.y + z*v.z;
	}
	Vecteur operator/(float v){
		Vecteur ret;
		ret.x = x/v;
		ret.y = y/v;
		ret.z = z/v;
		return ret;
	}
	void normalise(){
		float length = sqrt(x*x+y*y+z*z);
		x/=length;
		y/=length;
		z/=length;
	}
	float getLength(){
		return sqrt(x*x+y*y+z*z);
	}
	Vecteur cross(const Vecteur& v){
		Vecteur ret;
		ret.x = y*v.z - z*v.y;
		ret.y = z*v.x - x*v.z;
		ret.z = x*v.y - y*v.x;
		return ret;
	}
	
};
struct TexCoord
{
	float u,v;
};
struct Color
{
	float r,g,b;
	void set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};
/**
 * structure definissant les informations necessaires pour les faces.
 */
struct Face
{
	/**
	 * les index des vertex
	 */
	unsigned int vertexIndex[3];
	/**
	 * les index dex coordonnées de texture
	 */
	unsigned int texCoordIndex[3];
	/**
	 * les index des normales
	 */
	unsigned int normalIndex[3];
};

/**
 * classe permettant de gerer un model qui va subit notre eclairage.
 */
class Model
{
private:
	/**
	 * le tableau de vertex
	 */
	Vecteur * vertex;
	/**
	 * le tableau de normales
	 */
	Vecteur * normals;
	/**
	 * le tableau de binormales (il y a autant de binormal que de normal)
	 */
	Vecteur * binormals;
	/** 
	 * le tableau de tangente (il y a autant de tangente que de normales);
	 */
	Vecteur * tangents;
	/**
	 * le tableau de coordonnée de textures
	 */
	TexCoord * texCoords;
	/**
	 * le tableau de faces
	 */
	Face * faces;
	/**
	 * le nombre de vertex
	 */
	int nbVertex;
	/**
	 * le nombre de normales
	 */
	int nbNormals;
	/**
	 * le nombre de coordonnée de texture
	 */
	int nbTexCoord;
	/**
	 * le nombre de faces
	 */
	int nbFaces;

	/**
	 * methode servant à calculer l'espace local des vertex d'une face
	 */
	void computeLocalSpace(Face &face);
public:
	Model(void);
	virtual ~Model(void);
	bool load(const std::string & filePath);
	void initLighting(const Color& ambiant);
	void renderColor(Light& light);
	void addLightPerVertex(Light& light);
	void addLightCubeMap(Light& light);
	void render();
	/**
	 * methode servant à afficher l'espace local des vertex de la scene
	 */
	void drawLocalSpace();
};

#endif
