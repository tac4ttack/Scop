#include "Light.h"
#include <math.h>

Light::Light(void)
{
	radius = 100;
	color.set(1,1,1);
	position.x = 0;
	position.y = 0;
	position.z = 0;

}

Light::~Light(void)
{
}

void Light::setRadius(float r)
{
	radius = fabs(r);
}

float Light::getRadius()
{
	return radius;
}

void Light::setColor(float r, float g, float b)
{
	color.set(r,g,b);
}

Color Light::getColor()
{
	return color;
}

void Light::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

Vecteur Light::getPosition()
{
	return position;
}

Vecteur Light::computeLighting(const Vecteur & position)
{
	Vecteur ret;
	ret.x = (this->position.x - position.x) / (radius) + 0.5f;
	ret.y = (this->position.y - position.y) / (radius) + 0.5f;
	ret.z = (this->position.z - position.z) / (radius) + 0.5f;
	return ret;
}