#pragma once
#include "utils\math_utils.h"

class Projectile
{
private:
	float xpos;
	float ypos;
	float zpos;
	float rot;


public:
	Projectile();
	Projectile(float x, float y, float z, float r);
	void setX(float t);
	void setY(float t);
	void setZ(float t);
	void setRot(float t);
	float getX();
	float getY();
	float getZ();
	float getRot();
	void move(int speed, float deltaTime);
};