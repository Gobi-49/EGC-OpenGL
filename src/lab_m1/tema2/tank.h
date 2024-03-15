#pragma once
#include "utils\math_utils.h"

class tank
{
private:
	int health;
	float xpos;
	float zpos;
	float rot;
	float canonRot;


public:
	tank();
	tank(int h);
	tank(int h, float x, float z, float r, float r2);
	void setX(float t);
	void setZ(float t);
	void setRot(float t);
	void setCanonRot(float t);
	void setHealth(int h);
	int getHealth();
	float getX();
	float getZ();
	float getRot();
	float getCanonRot();
	bool damage();
	void moveForward(int speed, float deltaTime);
	void moveBackward(int speed, float deltaTime);
	void moveLeft(int speed, float deltaTime);
	void moveRight(int speed, float deltaTime);
	void rotateLeft(int speed, float deltaTime);
	void rotateRight(int speed, float deltaTime);
	void rotateC(float angle);
};