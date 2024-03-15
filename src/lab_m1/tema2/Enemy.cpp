#include "Enemy.h"
#include<iostream>
Enemy::Enemy()
{
	t = tank();
	destX = 0;
	destZ = 0;
	state = 0;
	cooldown = 0;
}

Enemy::Enemy(int h)
{
	t = tank(h);
	destX = 0;
	destZ = 0;
	state = 0;
	cooldown = 0;
}

void Enemy::setTank(tank ta)
{
	t = ta;
}

void Enemy::setDest(float x, float z)
{
	destX = x;
	destZ = z;
}

float Enemy::getDestX()
{
	return destX;
}

float Enemy::getDestZ()
{
	return destZ;
}

void Enemy::setState(int s)
{
	state = s;
}

void Enemy::setCooldown(float s)
{
	cooldown = s;
}

float Enemy::getCooldown()
{
	return cooldown;
}

int Enemy::getState()
{
	return state;
}

tank* Enemy::getTank()
{
	return &t;
}

bool Enemy::makeCanon(float targetX, float targetZ, float deltaTime) {
	if (sqrt((targetX - t.getX()) * (targetX - t.getX()) + (targetZ - t.getZ()) * (targetZ - t.getZ())) < 4)
	{
		float angle = atan2(targetZ - t.getZ(), targetX - t.getX()) * 180 / 3.14;
		angle += 90;
		if (angle < 0) {
			angle += 360.0;
		}
		angle = 360 - angle;
		float angleDiff = angle - t.getCanonRot();
		angleDiff = fmod(angleDiff + 360.0, 360.0);
		if (angleDiff > 180.0) {
			angleDiff -= 360.0;
		}
		if (angleDiff > 0) {
			t.rotateLeft(15, deltaTime);
		}
		else if (angleDiff < 0) {
			t.rotateRight(15, deltaTime);
		}
		if (angleDiff < 15 && angleDiff > -15)
		{
			return true;
		}
	}
	return false;
}

void Enemy::makeMove(float deltaTime)
{
	if (t.getX() < destX + 0.6 && t.getX() > destX - 0.6 && 
		t.getZ() < destZ + 0.6 && t.getZ() > destZ - 0.6)
	{
		state = 0;
		return;
	}
	float angle = atan2(destZ - t.getZ(), destX - t.getX()) * 180 / 3.14;
	angle += 90;
	if (angle < 0) {
		angle += 360.0;
	}
	angle = 360 - angle;
	float angleDiff = angle - t.getCanonRot();
	angleDiff = fmod(angleDiff + 360.0, 360.0);
	if (angleDiff > 180.0) {
		angleDiff -= 360.0;
	}
	if (angleDiff > 0) {
		t.moveLeft(15, deltaTime);
	}
	else if (angleDiff < 0) {
		t.moveRight(15, deltaTime);
	}
	
	//printf("current: %f, %f\ndest: %f, %f\n\n", t.getX(), t.getZ(), destX, destZ);
	
	if (angleDiff < 3.0f && angleDiff > -3.0f) {
		t.moveForward(1.5f, deltaTime);
	}
}

void Enemy::decrementCooldown(float deltaTime)
{
	if (cooldown >= 0)
		cooldown -= deltaTime;
}
