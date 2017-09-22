#pragma once
class Obstacle
{
	public:
		Obstacle();
		Obstacle(float x, float y);
		Obstacle(float x, float y, ALLEGRO_BITMAP *img);
		~Obstacle();

		void Collide(Bullets &bullet);
		void DrawObstacle();

	protected:
	private:
		float x;
		float y;
		float boundx;
		float boundy;

		ALLEGRO_BITMAP *image;
};

