#pragma once
#include "gameObject.h"

class entity: public gameObject 
{
	private:
		int type;
		int health;
		float killScale;
		// 1 2 3 4 for turrets
		// -1 -2 -3 -4 for enemys
	public:
		entity();
		entity(float x, float y, int t);
		entity(float x, float y, int t, int health);
		entity(float x, float y, int t, float killScale);
		void setType(int t);
		void setHealth(int h);
		int getHealth();
		int getType();
		bool damage();
		float getKillScale();
		void setKillScale(float x);
		bool shrink(float deltaTime);
};