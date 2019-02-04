#include <stdlib.h>
#include <math.h>
#include "glew.h"
#include <GL/glut.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glext.h>

#include "TGA.h"
#include "Model.h"
#include "Light.h"
#include "shaders.h"

// le model sur lequel on va travailler
Model * model = NULL;
// l'identifiant de la texture utilisé par le model
unsigned int textureId;
// l'identifiant de la texture de normal map
unsigned int normalMapId;
// l'identifiant de la cube map de normalisation
unsigned int normalCubeMapId;
// l'identifiant de la heightmap
unsigned int heightMapId;
// l'identifiant de la gloss map
unsigned int glossMapId;
// l'identifiant de la texture de lightmap (ici, une texture 3D)
unsigned int lightmap;
// l'identifiant du vertex program
unsigned int vertexProgramId;
// l'identifiant du fragment program
unsigned int fragmentProgramId;
// la couleur ambiante de l'affichage
Color ambiant;
// la lumiere rouge
Light redLight;
// la lumiere bleu
Light blueLight;
// la lumiere blanche
Light whiteLight;

float angleRotationY = 0;
float cameraHeight = 8;
float whiteAngle = 0;
float whiteHeight = 3;
float whiteDistance = 4;
bool useWhiteLight = true;
bool drawLocalSpace = false;
/**
 * fonction appelé par GLUT pour dessiner la scene
 */
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float posX = cos(angleRotationY*(3.141/180))*8;
	float posZ = sin(angleRotationY*(3.141/180))*8;
	gluLookAt (posX,cameraHeight,posZ,0,0,0,0,1,0);

	// on configure la premiere unité de texture : elle contient la texture de la scene
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	// on effectue le rendu de la lumiere ambiante
	model->initLighting(ambiant);
	if (drawLocalSpace)
	{
		glDisable(GL_TEXTURE_2D);
		model->drawLocalSpace();
	}

	// on doit reconfigurer les unité de textures
	// la premiere unite de texture contient la normal map
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, normalMapId);

	// la deuxieme contient la texture de diffuse
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureId );

	// la troisieme contient la height map
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,heightMapId );

	// la quatrieme contient la gloss map
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,glossMapId );

	// la cinquieme contient la texture d'attenuation
	glActiveTextureARB(GL_TEXTURE4_ARB);
	glEnable(GL_TEXTURE_3D_EXT);
	glBindTexture(GL_TEXTURE_3D_EXT,lightmap );

	// on doit activer le blending additif pour pouvoir utiliser ce mode d'eclairage
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	glDepthMask(GL_FALSE);

	// on active les vertex/fragment program
	glEnable(GL_VERTEX_PROGRAM_ARB);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB,vertexProgramId);
	glEnable(GL_FRAGMENT_PROGRAM_ARB);
	glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB,fragmentProgramId);

	// on ajoute nos lumieres
	model->addLightCubeMap(redLight);
	model->addLightCubeMap(blueLight);
	if (useWhiteLight)
	{
		model->addLightCubeMap(whiteLight);
	}

	// on desactive les vertex/fragment program
	glDisable(GL_VERTEX_PROGRAM_ARB);
	glDisable(GL_FRAGMENT_PROGRAM_ARB);

	// on desactive la cinquieme unité de texture
	glActiveTextureARB(GL_TEXTURE4_ARB);
	glDisable(GL_TEXTURE_3D_EXT);
	// on desactive la quatrieme unité de texture
	glActiveTextureARB(GL_TEXTURE3_ARB);
	glDisable(GL_TEXTURE_2D);
	// on desactive la troisieme unité de texture
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glDisable(GL_TEXTURE_2D);
	// on desactive la seconde unité de texture
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	// on desactive la premiere unité de texture
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_CUBE_MAP_ARB);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	// on affiche les lumieres
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glColor3f(redLight.getColor().r,redLight.getColor().g,redLight.getColor().b);
		glVertex3f(redLight.getPosition().x,redLight.getPosition().y,redLight.getPosition().z);
		glColor3f(blueLight.getColor().r,blueLight.getColor().g,blueLight.getColor().b);
		glVertex3f(blueLight.getPosition().x,blueLight.getPosition().y,blueLight.getPosition().z);
		glColor3f(whiteLight.getColor().r,whiteLight.getColor().g,whiteLight.getColor().b);
		glVertex3f(whiteLight.getPosition().x,whiteLight.getPosition().y,whiteLight.getPosition().z);
	glEnd();
	glPointSize(1.0f);

	glutSwapBuffers();
	glFlush();
}

/**
 * fonction appelé par GLUT à la fin de la fonction de dessin
 */
void idle(void)
{

	// on demande à glut de redessiner la scene
	glutPostRedisplay();
}

/**
 * fonction appelé par GLUT lors de l'appuye sur un bouton de la souris
 * @param boutton : le bouton utilisé. peut etre GLUT_MIDDLE_BUTTON, GLUT_LEFT_BUTTON ou GLUT_RIGHT_BUTTON
 * @param etat : l'etat du boutton. peut etre GLUT_UP ou GLUT_DOWN
 * @param x : la position X du curseur de la souris
 * @param y : la position Y du curseur de la souris
 */
void mouse(int boutton,int etat,int x,int y)
{
}

/**
 * fonction appelé par GLUT lors de l'appuye sur une touche du clavier
 * @param key : la touche (en UNICODE) utilisée
 * @param x : la position X du curseur de la souris
 * @param y : la position Y du curseur de la souris
 */
void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 27:
			delete model;
			glutLeaveGameMode();
			exit(0); // quitte
		break;
		case '4':
			angleRotationY --;
			break;
		case '6':
			angleRotationY ++;
			break;
		case '8':
			cameraHeight ++;
			break;
		case '2':
			cameraHeight --;
			break;
		case '7':
			whiteAngle --;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case '9':
			whiteAngle ++;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case '-':
			whiteHeight ++;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case '+':
			whiteHeight --;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case '/':
			whiteDistance --;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case '*':
			whiteDistance ++;
			whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);
			break;
		case ' ':
			useWhiteLight = !useWhiteLight;
			break;
		case 'l':
			drawLocalSpace = !drawLocalSpace;
			break;
	}
}

/**
 * fonction appelé par GLUT lors du redimentionnement de la fenetre
 * @param width : la largeur de la fenetre
 * @param height : la hauteur de la fenetre
 */
void reshape(int width,int height)
{
	glViewport(0,0,(GLsizei) width,(GLsizei) height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,width/height,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * fonction utilisée pour initialiser openGL
 */
void initGLState()
{
	glClearColor(0,0,0,0);
	glClearDepth(1010);
	glDepthFunc(GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);
}

/**
 * fonction utilisée pour initialiser les callback glut
 */
void initCallback()
{
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
}

/**
 * fonction appelée pour initialiser les textures utilisées dans le programme
 */
void initTextures()
{
	glEnable(GL_TEXTURE_2D);
	TGA image;
	if (image.load("rock.tga"))
	{
		glGenTextures (1, &textureId); 
		glBindTexture(GL_TEXTURE_2D, textureId); 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		if (image.getBpp() == 24)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.getWidth(), image.getHeight(),GL_RGB, GL_UNSIGNED_BYTE, image.getDatas());  
		}
		else
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.getWidth(), image.getHeight(),GL_RGBA, GL_UNSIGNED_BYTE, image.getDatas());  
		}
	}
	else
	{
		fprintf(stderr,"impossible de charger l'image rock.tga");
		exit(0);
	}
	if (image.load("normal.tga"))
	{
		glGenTextures (1, &normalMapId); 
		glBindTexture(GL_TEXTURE_2D, normalMapId); 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		if (image.getBpp() == 24)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.getWidth(), image.getHeight(),GL_RGB, GL_UNSIGNED_BYTE, image.getDatas());  
		}
		else
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.getWidth(), image.getHeight(),GL_RGBA, GL_UNSIGNED_BYTE, image.getDatas());  
		}
	}
	else
	{
		fprintf(stderr,"impossible de charger l'image rock.tga");
		exit(0);
	}
	if (image.load("height.tga"))
	{
		glGenTextures (1, &heightMapId); 
		glBindTexture(GL_TEXTURE_2D, heightMapId); 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		if (image.getBpp() == 24)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.getWidth(), image.getHeight(),GL_RGB, GL_UNSIGNED_BYTE, image.getDatas());  
		}
		else
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.getWidth(), image.getHeight(),GL_RGBA, GL_UNSIGNED_BYTE, image.getDatas());  
		}
	}
	else
	{
		fprintf(stderr,"impossible de charger l'image rock.tga");
		exit(0);
	}
	if (image.load("gloss.tga"))
	{
		glGenTextures (1, &glossMapId); 
		glBindTexture(GL_TEXTURE_2D, glossMapId); 
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		if (image.getBpp() == 24)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.getWidth(), image.getHeight(),GL_RGB, GL_UNSIGNED_BYTE, image.getDatas());  
		}
		else
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.getWidth(), image.getHeight(),GL_RGBA, GL_UNSIGNED_BYTE, image.getDatas());  
		}
	}
	else
	{
		fprintf(stderr,"impossible de charger l'image rock.tga");
		exit(0);
	}
	glDisable(GL_TEXTURE_2D);
}

/**
 * fonction appelée pour initialiser les extension openGL
 */
void initExtensions()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// impossible d'initialiser glew
		fprintf(stderr, "Error a l'initialisation de GLEW : %s\n", glewGetErrorString(err));
		exit(0);
	}
	if (!glewIsSupported("GL_ARB_multitexture"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_multitexture\n");
		exit(0);
	}
	if (!glewIsSupported("GL_EXT_texture3D"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_multitexture\n");
		exit(0);
	}
	if (!glewIsSupported("GL_ARB_texture_env_dot3"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_texture_env_dot3\n");
		exit(0);
	}
	if (!glewIsSupported("GL_ARB_texture_cube_map"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_texture_cube_map\n");
		exit(0);
	}
	if (!glewIsSupported("GL_ARB_vertex_program"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_vertex_program\n");
		exit(0);
	}
	if (!glewIsSupported("GL_ARB_fragment_program"))
	{
		fprintf(stderr,"votre carte ne supporte pas l'extension GL_ARB_fragment_program\n");
		exit(0);
	}		
}

/**
 * fonction permettant de generer une texture 3D contenant une sphere attenuée pour
 * servire de lightmap.
 * @param size : la taille des coté de la texture.
 */
void generateSphereMap(int size)
{
	glEnable(GL_TEXTURE_3D_EXT);
	if(size<1)
	{
		fprintf(stderr,"la taille de la texture 3D doit etre superieur à 1\n");
		return;
	}

	float *datas = new float[size*size*size*3];
	//on remplie avec la couleur noir
	for(int i=0; i<size*size*size*3; i++)
	{
		datas[i] = 0.0f;
	}
	float length;
	//la demi largeur de la texture3d en texels
	float size2= (float)size / 2.0f;

	for(float i=0; i<size; i++)
	{
		for(float j=0; j<size; j++)
		{
			for(float k=0; k<size; k++)
			{
				//la demi-largeur moins la distance du centre au texel courant de la texture.
				//size2-1 pour éviter l'élairage sur le bord de la texture mais centre moins brillant
				length = (size2-1) - sqrt( (i-size2)*(i-size2) + (j-size2)*(j-size2) + (k-size2)*(k-size2) );
				//normalisation dans la plage[0,1] (intensité de la lumière)
				length /= size2;

				//on stocke la couleur avec son intensité dans le texel
				datas[(int)i*size*size*3 + (int)j*size*3 + (int)k*3   ] = length;
				datas[(int)i*size*size*3 + (int)j*size*3 + (int)k*3 +1] = length;
				datas[(int)i*size*size*3 + (int)j*size*3 + (int)k*3 +2] = length;
			}
		}
	}

	glGenTextures(1,&lightmap);
	glBindTexture(GL_TEXTURE_3D_EXT,lightmap);
	glTexParameteri(GL_TEXTURE_3D_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D_EXT, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage3DEXT(GL_TEXTURE_3D_EXT, 0, GL_RGB, size, size, size, 0, GL_RGB, GL_FLOAT, datas);

	glDisable(GL_TEXTURE_3D_EXT);
	delete [] datas;
}

/**
 * fonction servant a retourner un vecteur de la cube map de normalisation pointant vers le centre
 * de la cube map
 * note : ce code provient des demo nVidia sur le bump mapping
 * @param i : le numero de la face de la cubemap sur laquel on travail
 * @param cubesize : la taille d'un coté de la cube map (en texel)
 * @param x : la position X du texel dans la face de la cube map
 * @param y : la position Y du texel dans la face de la cube map
 * @param vector : tableau de 3 float dans lequel sera stocké le resultat
 */
void getCubeVector(int i, int cubesize, int x, int y, float *vector)
{
	float s, t, sc, tc, mag;

	s = ((float)x + 0.5) / (float)cubesize;
	t = ((float)y + 0.5) / (float)cubesize;
	sc = s*2.0 - 1.0;
	tc = t*2.0 - 1.0;

	switch (i) {
		case 0:
			vector[0] = 1.0;
			vector[1] = -tc;
			vector[2] = -sc;
			break;
		case 1:
			vector[0] = -1.0;
			vector[1] = -tc;
			vector[2] = sc;
			break;
		case 2:
			vector[0] = sc;
			vector[1] = 1.0;
			vector[2] = tc;
			break;
		case 3:
			vector[0] = sc;
			vector[1] = -1.0;
			vector[2] = -tc;
			break;
		case 4:
			vector[0] = sc;
			vector[1] = -tc;
			vector[2] = 1.0;
			break;
		case 5:
			vector[0] = -sc;
			vector[1] = -tc;
			vector[2] = -1.0;
			break;
	}

	mag = 1.0/sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
	vector[0] *= mag;
	vector[1] *= mag;
	vector[2] *= mag;
}

void generateNormalisationCubeMap(int size)
{
	glEnable(GL_TEXTURE_CUBE_MAP_ARB);
	//genere l'objet de texture OpenGL en mémoire vidéo
	glGenTextures(1,&normalCubeMapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, normalCubeMapId);
	
	
	float vector[3];
	int i, x, y;
	GLubyte *pixels = new GLubyte[size*size*3];
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	for (i = 0; i < 6; i++) {
		for (y = 0; y < size; y++) {
			for (x = 0; x < size; x++) {
				getCubeVector(i, size, x, y, vector);
				//
				// Moi je met les valeur en négatif comme sa on a directement le vecteur allant de la surface à la lumière.
				//==> pas la peine de faire des négation au moment du rendu
				//
				pixels[3*(y*size+x) + 0] = 128 - 127*vector[0];
				pixels[3*(y*size+x) + 1] = 128 - 127*vector[1];
				pixels[3*(y*size+x) + 2] = 128 - 127*vector[2];
			}
		}
		gluBuild2DMipmaps(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB+i,GL_RGB8,size,size,GL_RGB,GL_UNSIGNED_BYTE,pixels);
	}
	
	delete [] pixels;
		
	glDisable(GL_TEXTURE_CUBE_MAP_ARB);
}

void initShaders()
{
	glGenProgramsARB(1, &fragmentProgramId);
	glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragmentProgramId);
	glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,strlen((char*) fragmentProgram), fragmentProgram);

	if(GL_INVALID_OPERATION == glGetError() )
	{
		//une erreur est détectée
		//récupère les informations sur l'erreur survenue
		const unsigned char* errorString;
		GLint errorPos = 0;
		errorString=glGetString(GL_PROGRAM_ERROR_STRING_ARB);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB,&errorPos);
		
		fprintf(stderr,"une erreur est survenue a la position : %d\n%s\n", errorPos, errorString);
		// on affiche le program jusqu'a l'erreur
		for (int i = 0; i < errorPos; i++)
		{
			printf("%c", fragmentProgram[i]);
		}
		printf("\n");
	}

	// chargement du vertex program
	glGenProgramsARB(1, &vertexProgramId);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vertexProgramId);
	glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,strlen((char*) vertexProgram), vertexProgram);

	if(GL_INVALID_OPERATION == glGetError())
	{
		//une erreur est détectée
		//récupère les informations sur l'erreur survenue
		const unsigned char* errorString;
		GLint errorPos = 0;
		errorString=glGetString(GL_PROGRAM_ERROR_STRING_ARB);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB,&errorPos);
		
		fprintf(stderr,"une erreur est survenue a la position : %d\n%s\n", errorPos, errorString);
		// on affiche le program jusqu'a l'erreur
		for (int i = 0; i < errorPos; i++)
		{
			printf("%c", vertexProgram[i]);
		}
		printf("\n");
	}
}

/**
 * Fonction principal du programme
 */
void main(int argc,char** argv)
{
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutGameModeString("1024x768:32@85");
	glutEnterGameMode();
	/*glutInitWindowSize(1024,768);
	glutCreateWindow("projet");*/

	initGLState();
	initExtensions();
	initTextures();
	initCallback();
	generateSphereMap(64);
	generateNormalisationCubeMap(128);
	initShaders();

	model = new Model();
	ambiant.set(0.1,0.1,0.1);
	if (!model->load("scene.obj")){
		fprintf(stderr,"impossible de charger le fichier scene.obj");
		delete model;
		exit(0);
	}
	redLight.setColor(1,0,0);
	redLight.setPosition(5,5,0);
	redLight.setRadius(15);
	blueLight.setColor(0,0,1);
	blueLight.setPosition(-5,5,0);
	blueLight.setRadius(20);
	whiteLight.setColor(1,1,1);
	whiteLight.setRadius(20);
	whiteLight.setPosition(cos(whiteAngle*(3.141/180))*whiteDistance,whiteHeight,sin(whiteAngle*(3.141/180))*whiteDistance);

	glutMainLoop();
}
