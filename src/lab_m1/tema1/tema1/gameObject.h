#pragma once

class gameObject
{
	private:
		float posX, posY;
		
	public:
		gameObject();
		gameObject(float x, float y);

		void setPosition(float posX, float posY);
		void setX(float posX);
		void setY(float posY);
		float getX();
		float getY();
};
