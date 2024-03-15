#include "currency.h"

currency::currency() : gameObject()
{
}

currency::currency(int x, int y, int eX, int eY) : gameObject(x, y)
{
	expectedX = eX;
	expectedY = eY;
}


void currency::setExpectedX(int x)
{
	expectedX = x;
}

void currency::setExpectedY(int y)
{
	expectedY = y;
}

int currency::getExpectedX()
{
	return expectedX;
}

int currency::getExpectedY()
{
	return expectedY;
}
