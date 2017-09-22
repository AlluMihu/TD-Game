#pragma once

class Terrorist: public Enemy
{
	public:
		Terrorist();
		Terrorist(float x1, float y1, ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2, ALLEGRO_BITMAP *img3);
		~Terrorist();
		
		void UpdateEnemy();
		void DrawEnemy(int time);
		void Die(Bullets &bullet);

		void setLive(bool x);
		bool isLive();
		bool endOfTheRoad();
	protected:
	private:
		float speed;
		float x;
		float y;
		float boundx;
		float boundy;
		bool live;

		ALLEGRO_BITMAP *image1;
		ALLEGRO_BITMAP *image2;
		ALLEGRO_BITMAP *image3;
};

