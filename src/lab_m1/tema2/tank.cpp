#include "tank.h"

tank::tank()
{
	xpos = 0;
	zpos = 0;
	rot = 0;
	canonRot = 0;
	health = 0;
}

tank::tank(int h)
{
	xpos = 0;
	zpos = 0;
	rot = 0;
	canonRot = 0;
	health = h;
}

tank::tank(int h, float x, float z, float r, float r2)
{
	health = h;
	xpos = x;
	zpos = z;
	rot = r;
	canonRot = r2;
}

void tank::setX(float t)
{
	xpos = t;
}

void tank::setZ(float t)
{
	zpos = t;
}

void tank::setRot(float t)
{
	rot = t;
}

void tank::setCanonRot(float t)
{
	canonRot = t;
}

void tank::setHealth(int h)
{
	health = h;
}

int tank::getHealth()
{
	return health;
}

float tank::getX()
{
	return xpos;
}

float tank::getZ()
{
	return zpos;
}

float tank::getRot()
{
	return rot;
}

float tank::getCanonRot()
{
	return canonRot;
}

bool tank::damage()
{
	health--;
	if (health == 0)
		return false;
	else
		return true;
}

void tank::moveForward(int speed, float deltaTime)
{
	xpos -= speed * deltaTime * sin(RADIANS(rot));
	zpos -= speed * deltaTime * cos(RADIANS(rot));
}

void tank::moveBackward(int speed, float deltaTime)
{
	xpos += speed * deltaTime * sin(RADIANS(rot));
	zpos += speed * deltaTime * cos(RADIANS(rot));
}

void tank::moveLeft(int speed, float deltaTime)
{
	rot += speed * deltaTime;
	canonRot += speed * deltaTime;
}

void tank::moveRight(int speed, float deltaTime)
{
	rot -= speed * deltaTime;
	canonRot -= speed * deltaTime;
}

void tank::rotateLeft(int speed, float deltaTime)
{
	canonRot += speed * deltaTime;
}

void tank::rotateRight(int speed, float deltaTime)
{
	canonRot -= speed * deltaTime;
}

void tank::rotateC(float angle)
{
	canonRot += angle;
}
