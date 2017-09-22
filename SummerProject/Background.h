#pragma once

class Background
{
	public:
		Background();
		Background(float x1, float y1, float width1, float height1, ALLEGRO_BITMAP *image1);
		~Background();

		void DrawBackground();

	protected:
	private:
		int x;
		int y;
		int width;
		int height;

		ALLEGRO_BITMAP *image;
};

