#include "Model.h"
#include "OBJReader.h"
#include "Light.h"
#include <math.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "glew.h"
#include <GL/gl.h>
#include <GL/glext.h>

Model::Model(void)
{
	vertex = NULL;
	normals = NULL;
	binormals = NULL;
	tangents = NULL;
	texCoords = NULL;
	faces = NULL;
	nbVertex = 0;
	nbNormals = 0;
	nbTexCoord = 0;
	nbFaces = 0;
}

Model::~Model(void)
{
	delete[] vertex;
	delete[] normals;
	delete[] binormals;
	delete[] tangents;
	delete[] texCoords;
	delete[] faces;
}

bool Model::load(const std::string & filePath)
{
	// on crée un lecteur de .obj
	OBJReader reader(filePath);
	// on charge le model
	if (reader.load())
	{
		// le model est bien charge
		// on alloue le tableau de vertex
		vertex = new Vecteur[reader.getVertex().size()];
		nbVertex = 0;
		// on copie les informations des vertex
		for (std::vector<OBJReader::OBJVector>::iterator it = reader.getVertex().begin(); it != reader.getVertex().end(); ++it)
		{
			vertex[nbVertex].x = (*it).x;
			vertex[nbVertex].y = (*it).y;
			vertex[nbVertex].z = (*it).z;
			nbVertex++;
		}
		// on alloue le tableau de normales
		normals = new Vecteur[nbVertex];
		binormals = new Vecteur[nbVertex];
		tangents = new Vecteur[nbVertex];
		// on les initialises au vecteur null
		for (int i = 0; i < nbVertex; i++)
		{
			normals[i].x = normals[i].y = normals[i].z = binormals[i].x = binormals[i].y = 
			binormals[i].z = tangents[i].x = tangents[i].y = tangents[i].z = 0.0f;
		}
		// on alloue le tableau de coordonnée de textures
		texCoords = new TexCoord[reader.getTexture().size()];
		nbTexCoord = 0;
		// on copie les informations de coordonnée de texture
		for (std::vector<OBJReader::OBJtexCoord>::iterator it = reader.getTexture().begin(); it != reader.getTexture().end(); ++it)
		{
			texCoords[nbTexCoord].u = (*it).u;
			texCoords[nbTexCoord].v = (*it).v;
			nbTexCoord++;
		}
		// on alloue le tableau de faces
		faces = new Face[reader.getFace().size()];
		nbFaces = 0;
		// on copie les informations des faces
		for (std::vector<OBJReader::OBJface>::iterator it = reader.getFace().begin(); it != reader.getFace().end(); ++it)
		{
			faces[nbFaces].vertexIndex[0] = (*it).vertex[0];
			faces[nbFaces].vertexIndex[1] = (*it).vertex[1];
			faces[nbFaces].vertexIndex[2] = (*it).vertex[2];
			faces[nbFaces].normalIndex[0] = (*it).normal[0];
			faces[nbFaces].normalIndex[1] = (*it).normal[1];
			faces[nbFaces].normalIndex[2] = (*it).normal[2];
			faces[nbFaces].texCoordIndex[0] = (*it).texture[0];
			faces[nbFaces].texCoordIndex[1] = (*it).texture[1];
			faces[nbFaces].texCoordIndex[2] = (*it).texture[2];
			nbFaces++;
		}

		// maintenant que nous avons toutes les information sur les faces, on peut calculer l'espace local
		for (int i = 0; i < nbFaces; i++)
		{
			computeLocalSpace(faces[i]);
		}
		// il ne faut pas oublier de renormaliser les tangentes et binormales
		for (int i = 0; i < nbVertex; i++){
			binormals[i].normalise();
			tangents[i].normalise();
			normals[i].normalise();
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Model::renderColor(Light& light)
{
	glColor3f(light.getColor().r,light.getColor().g,light.getColor().b);
	Vecteur lightPos = light.getPosition();
	glBegin(GL_TRIANGLES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			Vecteur &v = vertex[faces[i].vertexIndex[j]];
			Vecteur lightTexCoord = light.computeLighting(v);
			// la premiere unité de texture contient la texture d'attenuation
			glMultiTexCoord3fARB(GL_TEXTURE0_ARB,lightTexCoord.x,lightTexCoord.y,lightTexCoord.y);
			glVertex3f(v.x,v.y,v.z);
		}
	}
	glEnd();
}

void Model::addLightPerVertex(Light& light)
{
	Vecteur lightPos = light.getPosition();
	glBegin(GL_TRIANGLES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			int vertexIndex = faces[i].vertexIndex[j];
			// on calcule le vecteur vertex->lumiere normalise
			Vecteur vertexToLight;
			vertexToLight.x = lightPos.x - vertex[vertexIndex].x;
			vertexToLight.y = lightPos.y - vertex[vertexIndex].y;
			vertexToLight.z = lightPos.z - vertex[vertexIndex].z;
			// maintenant, il faut projeter ce vecteur dans l'espace local du vertex
			int normalIndex = faces[i].normalIndex[j];
			vertexToLight.x = tangents[vertexIndex].x*vertexToLight.x + tangents[vertexIndex].y*vertexToLight.y + tangents[vertexIndex].z*vertexToLight.z;
			vertexToLight.y = binormals[vertexIndex].x*vertexToLight.x + binormals[vertexIndex].y*vertexToLight.y + binormals[vertexIndex].z*vertexToLight.z;
			vertexToLight.z = normals[vertexIndex].x*vertexToLight.x + normals[vertexIndex].y*vertexToLight.y + normals[vertexIndex].z*vertexToLight.z;
			// on normalise
			float length = sqrt(vertexToLight.x*vertexToLight.x + vertexToLight.y*vertexToLight.y + vertexToLight.z*vertexToLight.z);
			vertexToLight.x /= length;
			vertexToLight.y /= length;
			vertexToLight.z /= length;
			// nous avons donc maintenant le vecteur du vertex vers la lumiere transformer dans l'espace local du vertex.
			// on l'envoie sous forme de couleur a openGL
			glColor3f(vertexToLight.x,vertexToLight.y,vertexToLight.z);
			// maintenant, on envoie les coordonner de textures
			// la premiere unite de texture contient la normal map, ce sont donc les même coordonnée de textures que
			// la scene
			TexCoord &tc = texCoords[faces[i].texCoordIndex[j]];
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,tc.u,tc.v);
			// la deuxieme unite de texture contient la texture 3D d'attenuation, on calcule donc l'eclairage
			Vecteur &v = vertex[vertexIndex];
			Vecteur lightTexCoord = light.computeLighting(v);
			glMultiTexCoord3fARB(GL_TEXTURE1_ARB,lightTexCoord.x,lightTexCoord.y,lightTexCoord.y);
			// la troisieme unité de texture contient la texture de diffuse, donc les coordonnée de texture de la scene
			glMultiTexCoord2fARB(GL_TEXTURE2_ARB,tc.u,tc.v);
			glVertex3f(v.x,v.y,v.z);
		}
	}
	glEnd();
}

void Model::addLightCubeMap(Light& light)
{
	Vecteur lightPos = light.getPosition();
	// on passe la couleur de la lumiere
	glColor3f(light.getColor().r,light.getColor().g,light.getColor().b);
	// on passe la position de la lumiere et son rayon dans la coordonnée de texture 1
	glMultiTexCoord4fARB(GL_TEXTURE1_ARB,lightPos.x,lightPos.y,lightPos.z,1/light.getRadius());
	glBegin(GL_TRIANGLES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			int vertexIndex = faces[i].vertexIndex[j];
			// on passe les tangents, binormal et normals dans les coordonnée de texture 2,3 et 4
			glMultiTexCoord3fARB(GL_TEXTURE2_ARB,tangents[vertexIndex].x,tangents[vertexIndex].y,tangents[vertexIndex].z);
			glMultiTexCoord3fARB(GL_TEXTURE3_ARB,binormals[vertexIndex].x,binormals[vertexIndex].y,binormals[vertexIndex].z);
			glMultiTexCoord3fARB(GL_TEXTURE4_ARB,normals[vertexIndex].x,normals[vertexIndex].y,normals[vertexIndex].z);
			// on passe les coordonnée de la scene dans la coordonnée de texture 0
			TexCoord &tc = texCoords[faces[i].texCoordIndex[j]];
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,tc.u,tc.v);
			Vecteur &v = vertex[vertexIndex];
			glVertex3f(v.x,v.y,v.z);
		}
	}
	glEnd();
}

void Model::render()
{
	glColor3f(1,1,1);
	glBegin(GL_TRIANGLES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			TexCoord &tc = texCoords[faces[i].texCoordIndex[j]];
			Vecteur &v = vertex[faces[i].vertexIndex[j]];
			glTexCoord2f(tc.u,tc.v);
			glVertex3f(v.x,v.y,v.z);
		}
	}
	glEnd();
}

void Model::initLighting(const Color& ambiant)
{
	glColor3f(ambiant.r,ambiant.g,ambiant.b);
	glBegin(GL_TRIANGLES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			TexCoord &tc = texCoords[faces[i].texCoordIndex[j]];
			Vecteur &v = vertex[faces[i].vertexIndex[j]];
			glTexCoord2f(tc.u,tc.v);
			glVertex3f(v.x,v.y,v.z);
		}
	}
	glEnd();
}

void Model::drawLocalSpace()
{
	glBegin(GL_LINES);
	for(int i = 0;i < nbFaces; i++){
		for (int j = 0; j < 3; j++){
			int vertexIndex = faces[i].vertexIndex[j];
			Vecteur &v = vertex[vertexIndex];
			// tangente en rouge
			Vecteur tangent = tangents[vertexIndex] + v;
			glColor3f(1,0,0);
			glVertex3f(v.x,v.y,v.z);
			glVertex3f(tangent.x,tangent.y,tangent.z);
			// binormal en vert
			Vecteur binormal = binormals[vertexIndex] + v;
			glColor3f(0,1,0);
			glVertex3f(v.x,v.y,v.z);
			glVertex3f(binormal.x,binormal.y,binormal.z);
			// normal en bleu
			Vecteur normal = normals[vertexIndex] + v;
			glColor3f(0,0,1);
			glVertex3f(v.x,v.y,v.z);
			glVertex3f(normal.x,normal.y,normal.z);

		}
	}
	glEnd();
}

void Model::computeLocalSpace(Face &face)
{
	// on calcule 2 vecteur formant les bord du triangle
	// le vecteur side0 est celui allant du vertex 0 au vertex 1
	Vecteur side0 = vertex[face.vertexIndex[1]] - vertex[face.vertexIndex[0]];
	// le vecteur side1 est celui allant du vertex 0 au vertex 2
	Vecteur side1 = vertex[face.vertexIndex[2]] - vertex[face.vertexIndex[0]];

	// ici on calcule la normale à la face
	Vecteur normal = side0.cross(side1);
	normal.normalise();

	// maintenant on calcule les coefficient des tangentes
	// ces coefficient sont fonction des coordonnée de texture du polygone
	float deltaT0 = texCoords[face.texCoordIndex[1]].v - texCoords[face.texCoordIndex[0]].v;
	float deltaT1 = texCoords[face.texCoordIndex[2]].v - texCoords[face.texCoordIndex[0]].v;
	// on effectue la même chose pour la binormal
	float deltaB0 = texCoords[face.texCoordIndex[1]].u - texCoords[face.texCoordIndex[0]].u;
	float deltaB1 = texCoords[face.texCoordIndex[2]].u - texCoords[face.texCoordIndex[0]].u;
	float scale = 1/ ((deltaB0 * deltaT1) - (deltaB1 * deltaT0));

	// on calcule la tangente temporaire
	Vecteur tmpTangente = ((side0*deltaT1) - (side1*deltaT0))*scale;
	tmpTangente.normalise();

	// on calcule la binormal temporaire
	Vecteur tmpBinormal = ((side0*(-deltaB1)) + (side1*deltaB0))*scale;
	tmpBinormal.normalise();

	// nous avons donc maintenant les tangente, binormale et normale de la face. on les additionne à celles deja presente
	// dans les tableaux
	tangents[face.vertexIndex[0]] += tmpTangente;
	tangents[face.vertexIndex[1]] += tmpTangente;
	tangents[face.vertexIndex[2]] += tmpTangente;

	binormals[face.vertexIndex[0]] += tmpBinormal;
	binormals[face.vertexIndex[1]] += tmpBinormal;
	binormals[face.vertexIndex[2]] += tmpBinormal;

	normals[face.vertexIndex[0]] += normal;
	normals[face.vertexIndex[1]] += normal;
	normals[face.vertexIndex[2]] += normal;

}

