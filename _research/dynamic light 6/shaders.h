#ifndef SHADER_H
#define SHADER_H

#ifndef SIMPLE_SHADER
/**
 * vertex program utiliser pour gerer l'eclairage
 * @param vertex.texcoord[0] : coordonnée de texture du polygone
 * @param vertex.texcoord[1] : position de la lumiere + rayon dans w
 * @param vertex.texcoord[2] : tangente
 * @param vertex.texcoord[3] : binormal
 * @param vertex.texcoord[4] : normale
 * @param vertex.texcoord[5] : position de la camera
 * @param vertex.color : couleur de la lumiere
 *
 * @out result.texcoord[0] : coordonnée de texture du polygone
 * @out result.texcoord[1] : vecteur du vertex vers la camera
 * @out result.texcoord[2] : vecteur du vertex vers la lumiere
 * @out result.texcoord[3] : vecteur du vertex vers la lumiere non transformé dans l'espace local
 */
const unsigned char vertexProgram[] = 
	"!!ARBvp1.0 OPTION ARB_position_invariant;\n"

	"PARAM	mvit[4] = {state.matrix.modelview.invtrans};\n"
	"PARAM	modelView[4]	= { state.matrix.modelview };\n"
	"PARAM	camPos = state.matrix.modelview.invtrans.row[3];\n"
	"ATTRIB	tangent	= vertex.texcoord[2];\n"
	"ATTRIB	binormal	= vertex.texcoord[3];\n"
	"ATTRIB	normal 	= vertex.texcoord[4];\n"
	"ATTRIB	lightInfo	= vertex.texcoord[1];\n"
	"TEMP	vertexToLight;\n"
	"TEMP	vertexToCam;\n"
	"TEMP	temp;\n"

	"SUB	temp, lightInfo, vertex.position ;\n"
	"MOV	result.texcoord[3], temp;"
	"MOV	result.texcoord[3].w, lightInfo.w;\n"

	"DP3	vertexToLight.x, temp, tangent;\n"
	"DP3	vertexToLight.y, temp, binormal;\n"
	"DP3	vertexToLight.z, temp, normal;\n"

	"SUB	temp, camPos, vertex.position;\n"
	"DP3	vertexToCam.x, temp, tangent;\n"
	"DP3	vertexToCam.y, temp, binormal;\n"
	"DP3	vertexToCam.z, temp, normal;\n"

	"MOV	result.texcoord[0], vertex.texcoord[0];\n"
	"MOV	result.texcoord[1], vertexToCam;"
	"MOV	result.texcoord[2], vertexToLight;"
	"MOV	result.color, vertex.color;\n"
	"END";

/** fragment program gerant l'affichage de la lumiere
 * @param texture[0] : normal map
 * @param texture[1] : diffuse map
 * @param texture[2] : height map
 * @param texture[3] : gloss map
 * @param texture[4] : attenuation map
 * @param fragment.texcoord[0] : coordonnée de texture du polygone
 * @param fragment.texcoord[1] : vecteur du fragment vers la camera
 * @param fragment.texcoord[2] : vecteur de fragment vers la lumiere
 * @param fragment.texcoord[3] : vecteur de fragment vers la lumiere dans l'espace global
 * @param fragment.color : la couleur de la lumiere
 */
const unsigned char fragmentProgram[] = 
	"!!ARBfp1.0 OPTION ARB_precision_hint_fastest;\n"
	"PARAM	power = {8,0,0,0};\n"
	"TEMP	normal;\n" // la texture de normal map
	"TEMP	attenuation;\n" // la texture d'attenuation
	"TEMP	diffuse;\n" // la texture de diffuse
	"TEMP	gloss;\n" // la texture de gloss
	"TEMP	height;\n" // la texture de height map
	"TEMP	newTexcoord;\n" // les coordonnée de textures modifiée par la parallax mapping
	"TEMP	toLight;\n" // le vecteur allans du fragment vers la lumiere
	"TEMP	final;\n" // la couleur final du fragment
	"TEMP	NdotL;\n" // le resultat du produit scalaire entre la normal et le vecteur vers la lumiere
	"TEMP	temp;\n" // vecteur temporaire
	"TEMP	halfAngle;\n" // le vecteur de demi angle pour le speculaire
	"TEMP	toCamera;\n" // le vecteur du fragment vers la camera
	"TEMP	specular;\n" // la composante spaculaire de la lumiere

	// on normalise le vecteur fragment->lumiere
	"DP3	temp, fragment.texcoord[2], fragment.texcoord[2];\n"
	"RSQ	temp, temp.x;\n"
	"MUL	toLight, fragment.texcoord[2], temp;\n"

	// on normalise le vecteur fragment->camera
	"DP3	temp, fragment.texcoord[1], fragment.texcoord[1];\n"
	"RSQ	temp, temp.x;\n"
	"MUL	toCamera, fragment.texcoord[1], temp;\n"

	// on calcule les nouvelle coordonnée de textures pour le parallax mapping
	"TEX	height, fragment.texcoord[0], texture[2], 2D;\n"
	"MAD	height, height, 0.04, -0.02;\n"
	"MAD	newTexcoord, height, toCamera, fragment.texcoord[0];\n"

	// on calcule l'attenuation
	// on a texcoord[3] qui contient le vecteur vertex->lumiere dans l'espace global
	// on divise le vecteur par le rayon de la lumiere (w contient l'inverse du rayon)
	// et on ajoute 0.5 pour partire du centre de la texture
	"MAD	attenuation, fragment.texcoord[3], fragment.texcoord[3].w, {0.5,0.5,0.5,0};\n"
	"TEX	attenuation, attenuation, texture[4], 3D;\n"

	// on charge la normal map
	"TEX	normal, newTexcoord, texture[0], 2D;\n"

	// on remap la normal dans [0..1] au lieu de [0.5..1]
	"MAD	normal, normal, 2, -1;\n"

	// on renormalise la normal
	"DP3	temp, normal, normal;\n"
	"RSQ	temp, temp.x;\n"
	"MUL	normal, normal, temp;\n"

	// on effectue le produit scalaire
	"DP3	NdotL, normal, toLight;\n"
	"MAX	NdotL, NdotL, 0;\n"
	"MUL_SAT	final, NdotL, fragment.color;\n"

	// on calcule le speculaire
	// on calcule le vecteur de demi angle
	"ADD	halfAngle, toCamera, toLight;\n"
	"DP3	temp, halfAngle, halfAngle;\n"
	"RSQ	temp, temp.x;\n"
	"MUL	halfAngle, halfAngle, temp;\n"
	// on effectue le calcule du produit scalaire
	"DP3	specular, normal, halfAngle;\n"
	"MAX	specular, specular, 0;\n"
	// on met le resultat a la puissante en parametre
	"POW	specular, specular.x, power.x;\n"

	// on multiplie par la couleur de la lumiere
	"MUL	specular, specular, fragment.color;\n"

	// on recupere les textures restantes
	"TEX	diffuse, newTexcoord, texture[1], 2D;\n"
	"TEX	gloss, newTexcoord, texture[3], 2D;\n"

	// on termine l'equation d'eclairage
	// on multiplie la composante speculaire par le gloss
	"MUL	specular, specular, gloss;\n"
	"MAD	final, final, diffuse, specular;\n"
	"MUL	final, final, attenuation;\n"

	"MOV	result.color, final;\n"

	"END";

#else
const unsigned char vertexProgram[] = 
	"!!ARBvp1.0 OPTION ARB_position_invariant;\n"

	"PARAM	mvit[4] = {state.matrix.modelview.invtrans};\n"
	"PARAM	modelView[4]	= { state.matrix.mvp };\n"
	"ATTRIB	tangent		= vertex.texcoord[2];\n"
	"ATTRIB	binormal	= vertex.texcoord[3];\n"
	"ATTRIB	normal 		= vertex.texcoord[4];\n"
	"ATTRIB	lightInfo	= vertex.texcoord[1];\n"
	"TEMP	vertexToLight;\n"
	"TEMP	temp;\n"
	"SUB	temp, lightInfo, vertex.position;\n"
	"DP3	vertexToLight.x, temp, tangent;\n"
	"DP3	vertexToLight.y, temp, binormal;\n"
	"DP3	vertexToLight.z, temp, normal;\n"

	"MOV	result.texcoord[2], vertexToLight;"
	"MOV	result.texcoord[0], vertex.texcoord[0];\n"
	"MOV	result.color, vertex.color;\n"
	"END";

const unsigned char fragmentProgram[] = 
	"!!ARBfp1.0 OPTION ARB_precision_hint_fastest;\n"
	"TEMP	normal;\n"
	"TEMP	toLight;\n"
	"TEMP	final;\n"
	"TEMP	NdotL;\n"
	"TEMP	temp;\n"

	// on normalise le vecteur fragment->lumiere
	"DP3	temp, fragment.texcoord[2], fragment.texcoord[2];\n"
	"RSQ	temp, temp.x;\n"
	"MUL	toLight, fragment.texcoord[2], temp;\n"

	// on recupere la normal
	"TEX	normal, fragment.texcoord[0], texture[0], 2D;\n"

	// remove scale and bias
	"MAD	normal, normal, 2, -1;\n"

	"DP3	NdotL, normal, toLight;\n"
	"MUL	final, NdotL, fragment.color;\n"
	"MOV	result.color, final;\n"
	"END";
#endif
#endif