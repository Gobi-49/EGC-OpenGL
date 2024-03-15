#include "player.h"

player::player()
{
	health = 0;
	money = 0;
	moneyMax = 0;
}

player::player(int h, int m, int max)
{
	health = h;
	money = m;
	moneyMax = max;
}

void player::setHealth(int x)
{
	health = x;
}

void player::setMoney(int t)
{
	money = t;
}

int player::getHealth()
{
	return health;
}

int player::getMoney()
{
	return money;
}

void player::incrementMoney()
{
	if(money < moneyMax)
	{
		money++;
	}
}

bool player::buy(int price)
{
	if (money - price >= 0) 
	{
		money -= price;
		return true;
	}
	return false;
}

bool player::damage()
{
	health--;
	if (health > 0)
		return true;
	else
		return false;
}
