#include "entity.h"

entity::entity() : gameObject()
{
	type = 0;
	health = 0;
	killScale = 0;
}

entity::entity(float x, float y, int t) : gameObject(x, y)
{
	type = t;
	health = 1;
	killScale = 0;
}

entity::entity(float x, float y, int t, int h) : entity(x, y, t)
{
	health = h;
}

entity::entity(float x, float y, int t, float ks) : gameObject(x, y)
{
	type = t;
	health = 0;
	killScale = ks;
}

void entity::setType(int t)
{
	type = t;
}

void entity::setHealth(int h)
{
	health = h;
}

int entity::getHealth()
{
	return health;
}

int entity::getType()
{
	return type;
}

bool entity::damage()
{
	health--;
	if (health == 0)
		return false;
	else
		return true;
}

float entity::getKillScale()
{
	return killScale;
}

void entity::setKillScale(float x)
{
	killScale = x;
}

bool entity::shrink(float deltaTime)
{
	killScale -= 1.5 * deltaTime;
	if (killScale <= 0)
		return true;
	return false;
}
