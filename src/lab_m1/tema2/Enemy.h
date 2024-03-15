#pragma once

#include "tank.h"

class Enemy
{
private:
	int state; // -1 dead / 0 no command / 1 has command
	tank t;
	float destX;
	float destZ;
	float cooldown;

public:
	Enemy();
	Enemy(int h);
	void setTank(tank t);
	void setDest(float x, float z);
	float getDestX();
	float getDestZ();
	void setState(int s);
	void setCooldown(float s);
	float getCooldown();
	int getState();
	tank* getTank();
	bool makeCanon(float targetX, float targetY, float deltaTime);
	void makeMove(float deltaTime);
	void decrementCooldown(float deltaTime);
};
