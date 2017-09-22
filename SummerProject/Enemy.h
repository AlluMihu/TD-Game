#pragma once

class Enemy
{
	public:
		Enemy();
		~Enemy();

		virtual void UpdateEnemy() = 0;
		virtual void DrawEnemy(int time) = 0;
	protected:
	private:
};

