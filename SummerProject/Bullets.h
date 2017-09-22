#pragma once

class Bullets
{
	public:
		Bullets();
		~Bullets();

		void UpdateBullet();
		void DrawBullet();
		void setLive(bool x);
		void setSpeedX(float x);
		void setSpeedY(float x);
		void setX(float z);
		void setY(float z);

		bool isLive();

		float getSpeed();
		float getSpeedX();
		float getSpeedY();
		float getX();
		float getY();
	protected:
	private:
		bool live;
		float x;
		float y;
		float speedX;
		float speedY;
		float speed;
};

