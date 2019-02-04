#ifndef LIGHT_H
#define LIGHT_H

#include "Model.h"

/**
 * classe gerant notre lumiere.
 */ 
class Light
{
private:
	float radius;
	Color color;
	Vecteur position;
public:
	Light(void);
	virtual ~Light(void);
	void setRadius(float r);
	float getRadius();
	void setColor(float r, float g, float b);
	Color getColor();
	void setPosition(float x, float y, float z);
	Vecteur getPosition();
	Vecteur computeLighting(const Vecteur & position);
};

#endif
