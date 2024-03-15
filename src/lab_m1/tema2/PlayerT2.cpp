#include "PlayerT2.h"

PlayerT2::PlayerT2()
{
	score = 0;
	t = tank();
}

PlayerT2::PlayerT2(int h)
{
	score = 0;
	t = tank(h);
}

void PlayerT2::setTank(tank ta)
{
	t = ta;
}

void PlayerT2::incrementScore()
{
	score++;
}

int PlayerT2::getScore()
{
	return score;
}

tank* PlayerT2::getTank()
{
	return &t;
}
