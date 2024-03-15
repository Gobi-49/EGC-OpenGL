#include "gameObject.h"
#include <iostream>

gameObject::gameObject()
{
	posX = 0;
	posY = 0;
}

gameObject::gameObject(float x, float y)
{
	posX = x;
	posY = y;
}

void gameObject::setPosition(float x, float y)
{
	posX = x;
	posY = y;
}

void gameObject::setX(float x)
{
	posX = x;
}

void gameObject::setY(float y)
{
	posY = y;
}

float gameObject::getX()
{
	return posX;
}

float gameObject::getY()
{
	return posY;
}
