// OBJReader.cpp: implementation of the OBJReader class.
//
//////////////////////////////////////////////////////////////////////

#include "OBJReader.h"

OBJReader::OBJReader()
{
	useTex = false;
	useNorm = false;
	file = "";
}

OBJReader::~OBJReader()
{
	this->face.clear();
	this->normal.clear();
	this->texture.clear();
	this->vertex.clear();
}

OBJReader::OBJReader(std::string fichier)
{
	file = fichier;
	useTex = false;
	useNorm = false;
}

bool OBJReader::load()
{
	bool ret = false;// variable retourné
	char c;// caractere temporaire qui sera lu comme entete de chaque ligne
	char temp[255] = {0};//chaine temporaire servant à passer à la ligne.

	// on ouvre le fichier en lecture seul
	fichier = fopen(file.c_str(),"r");
	// est ce que le fichier est bien ouvert ??
	if (fichier)
	{
		// tant qu'on est pas à la fin du fichier
		while (!feof(fichier))
		{
			// on lit le premier caractere de la ligne
			fscanf(fichier,"%c",&c);
			if (c == '\n' || c == '\0')// test le cas ou la ligne serait vide
			{
				continue;
			}
			// selon le caratere
			switch(c)
			{
			case 'v':// v c'est une info de vertex
				fscanf(fichier,"%c ", &c);
				switch (c)
				{
				case ' ':// vertex normal
					readVertex();
					break;
				case 'n':// normal du vertex
					readNormal();
					useNorm = true;
					break;
				case 't'://tex coord du vertex
					readTexture();
					useTex = true;
					break;
				}
				break;
			case 'f':// f c'est une face
				readFace();
				break;
			}
			c = ' ';
			// on passe a la ligne suivante.
			fgets(temp, 100, fichier);


		}
		ret = true;
		fclose(fichier);
	}
	return ret;
}

void OBJReader::readVertex()
{
	OBJVector tempVector;
	// on lit dans le fichier les infos du vertex
	fscanf(fichier,"%f %f %f",&tempVector.x,&tempVector.y,&tempVector.z);
	// et on ajoute le vecteur (au sens vecteur3D) a notre vecteur de stockage (std::vector)
	vertex.push_back(tempVector);
}

void OBJReader::readNormal()
{
	OBJVector tempVector;
	// on lit dans le fichier les infos du vertex
	fscanf(fichier,"%f %f %f",&tempVector.x,&tempVector.y,&tempVector.z);
	// et on ajoute le vecteur (au sens vecteur3D) a notre vecteur de stockage (std::vector)
	normal.push_back(tempVector);
}

void OBJReader::readTexture()
{
	OBJtexCoord temp;
	// lecture des info de texture
	fscanf(fichier," %f %f",&temp.u , & temp.v);
	// et sauvegarde de ses infos.
	texture.push_back(temp);
}

void OBJReader::readFace()
{
	OBJface temp;
	int t[9];
	if (useTex)
	{
		if(useNorm)
		{
			fscanf(fichier," %d/%d/%d %d/%d/%d %d/%d/%d",&t[0],&t[1],&t[2],&t[3],
														&t[4],&t[5],&t[6],&t[7],&t[8]);
		}
		else
		{
			fscanf(fichier," %d/%d %d/%d %d/%d",&t[0],&t[1],&t[3],&t[4],&t[6],&t[7]);
			t[2] = 0;
			t[5] = 0;
			t[9] = 0;
		}
	}
	else
	{
		if(useNorm)
		{
			fscanf(fichier," %d/%d %d/%d %d/%d",&t[0],&t[2],&t[3],&t[5],&t[6],&t[8]);
			t[1] = 0;
			t[4] = 0;
			t[7] = 0;
		}
		else
		{
			fscanf(fichier," %d %d %d",&t[0],&t[3],&t[6]);
			t[1] = 0;
			t[2] = 0;
			t[4] = 0;
			t[5] = 0;
			t[7] = 0;
			t[8] = 0;
		}
	}
	temp.vertex[0] = t[0]-1;
	temp.vertex[1] = t[3]-1;
	temp.vertex[2] = t[6]-1;
	temp.texture[0] = t[1]-1;
	temp.texture[1] = t[4]-1;
	temp.texture[2] = t[7]-1;
	temp.normal[0] = t[2]-1;
	temp.normal[1] = t[5]-1;
	temp.normal[2] = t[8]-1;
	face.push_back(temp);
}

void OBJReader::print(FILE * fichier)
{
	int i;
	for (i = 0; i < 3/*vertex.size()*/; i++)
	{
		fprintf(fichier,"v %f %f %f\n",vertex[i].x,vertex[i].y,vertex[i].z);
	}
	fprintf(fichier,"# %d vertices\n",vertex.size());
	for (i = 0; i < 3/*texture.size()*/; i++)
	{
		fprintf(fichier,"vt %f %f\n",texture[i].u,texture[i].v);
	}
	fprintf(fichier,"# %d texture coordinates\n",texture.size());
	for (i = 0; i < 3/*normal.size()*/; i++)
	{
		fprintf(fichier,"v %f %f %f\n",normal[i].x,normal[i].y,normal[i].z);
	}
	fprintf(fichier,"# %d normals\n",normal.size());
	for (i = 0; i < 3/*face.size()*/; i++)
	{
		fprintf(fichier,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					face[i].vertex[0],face[i].texture[0],face[i].normal[0],
					face[i].vertex[1],face[i].texture[1],face[i].normal[1],
					face[i].vertex[2],face[i].texture[2],face[i].normal[2]);
	}
	fprintf(fichier,"# %d faces\n",face.size());
}
