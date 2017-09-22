#pragma once
class Player
{
	public:
		Player();
		~Player();
		Player(ALLEGRO_BITMAP *playerBitmap);

		void MoveUp();
		void MoveDown();
		void DrawPlayer();
		void Shoot();
		void SetLive(int x);
		void SetScore(int x);

		float getX();
		float getY();
		int getLives();
		int getScore();

	protected:
	private:
		float x;
		float y;
		float boundx;
		float boundy;
		float speed;
		int lives;
		int score;

		ALLEGRO_BITMAP *image;
};

