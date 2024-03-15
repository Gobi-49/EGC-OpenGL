#pragma once

#include "tank.h"

class PlayerT2
{
private:
	int score;
	tank t;

public:
	PlayerT2();
	PlayerT2(int h);
	void setTank(tank t);
	void incrementScore();
	int getScore();
	tank* getTank();
};
