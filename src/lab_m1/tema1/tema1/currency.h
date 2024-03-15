#pragma once
#include "gameObject.h"

class currency : public gameObject
{
private:
	int expectedX;
	int expectedY;

public:
	currency();
	currency(int x, int y, int eX, int eY);
	void setExpectedX(int x);
	void setExpectedY(int t);
	int getExpectedX();
	int getExpectedY();
};
