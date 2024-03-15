#include "Projectile.h"

Projectile::Projectile()
{
	xpos = 0;
	ypos = 0;
	zpos = 0;
	rot = 0;
}

Projectile::Projectile(float x, float y, float z, float r)
{
	xpos = x;
	ypos = y;
	zpos = z;
	rot = r;
}

void Projectile::setX(float t)
{
	xpos = t;
}

void Projectile::setY(float t)
{
	ypos = t;
}

void Projectile::setZ(float t)
{
	zpos = t;
}

void Projectile::setRot(float t)
{
	rot = t;
}

float Projectile::getX()
{
	return xpos;
}

float Projectile::getY()
{
	return ypos;
}


float Projectile::getZ()
{
	return zpos;
}

float Projectile::getRot()
{
	return rot;
}

void Projectile::move(int speed, float deltaTime)
{
	xpos -= speed * deltaTime * sin(RADIANS(rot));
	zpos -= speed * deltaTime * cos(RADIANS(rot));
}