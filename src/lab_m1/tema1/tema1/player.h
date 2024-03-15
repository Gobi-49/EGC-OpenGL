#pragma once

class player
{
	private:
		int health;
		int money;
		int moneyMax;

	public:
		player();
		player(int h, int m, int max);
		void setHealth(int x);
		void setMoney(int t);
		int getHealth();
		int getMoney();
		void incrementMoney();
		bool buy(int type);
		bool damage();
};
